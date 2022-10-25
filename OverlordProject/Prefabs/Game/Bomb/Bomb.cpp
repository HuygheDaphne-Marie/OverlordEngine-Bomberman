#include "stdafx.h"
#include "Bomb.h"
#include "Utils/MathUtils.h"
#include "Components/BombPlacerComponent.h"

#include "Prefabs/Game/Tiles/UnbreakableBlock.h"
#include "Prefabs/Game/Tiles/BreakableBlock.h"
#include "Prefabs/Game/Player/Player.h"
#include "Prefabs/Game/Bomb/BombExplosion.h"

float Bomb::m_ExplosionCountdownDuration = 2.0f;

Bomb::Bomb(BombPlacerComponent* pPlacer, const XMINT2& coordinate, int explosionRadius)
	: TileEntity(coordinate.x, coordinate.y)
	, m_pPlacer(pPlacer)
	, m_ExplosionRadius{explosionRadius}
	, m_CountdownTimer{m_ExplosionCountdownDuration}
{
}

void Bomb::PlayerDestroyed(BombPlacerComponent* pPlacer)
{
	if (m_pPlacer == pPlacer)
	{
		m_pPlacer = nullptr;
	}
}

void Bomb::Initialize(const SceneContext& /*sceneContext*/)
{
	m_pMap = GetScene()->FindGameObjectWithTag(TileGridMap::m_TagName)->GetComponent<TileGridMap>();
	m_pPosition = GetComponent<GridCoordinateComponent>();
	m_pPosition->SetIsBlocking(true);

	// set our location to our grid position
	GetTransform()->Translate(m_pMap->GetTilePositionAt(m_pPosition->GetCoordinate()));

	SoundManager::Get()->GetSystem()->createSound("Resources/Sounds/retro_explosion.wav", FMOD_DEFAULT, nullptr, &m_pExplosionSound);

	// temp mesh
	{
		{
			//Create Cube
			const auto pMesh = new MeshDrawComponent(12);

			const float halfWidth = 0.5f / 2.f;
			const float halfHeight = 0.5f / 2.f;
			const float halfDepth = 0.5f / 2.f;
			const XMFLOAT4 m_Color{ Colors::Black };

			//FRONT
			pMesh->AddQuad(
				VertexPosNormCol(XMFLOAT3(-halfWidth, halfHeight, -halfDepth), XMFLOAT3(0, 0, -1), m_Color),
				VertexPosNormCol(XMFLOAT3(halfWidth, halfHeight, -halfDepth), XMFLOAT3(0, 0, -1), m_Color),
				VertexPosNormCol(XMFLOAT3(halfWidth, -halfHeight, -halfDepth), XMFLOAT3(0, 0, -1), m_Color),
				VertexPosNormCol(XMFLOAT3(-halfWidth, -halfHeight, -halfDepth), XMFLOAT3(0, 0, -1), m_Color)
			);

			//BACK
			pMesh->AddQuad(
				VertexPosNormCol(XMFLOAT3(halfWidth, halfHeight, halfDepth), XMFLOAT3(0, 0, 1), m_Color),
				VertexPosNormCol(XMFLOAT3(-halfWidth, halfHeight, halfDepth), XMFLOAT3(0, 0, 1), m_Color),
				VertexPosNormCol(XMFLOAT3(-halfWidth, -halfHeight, halfDepth), XMFLOAT3(0, 0, 1), m_Color),
				VertexPosNormCol(XMFLOAT3(halfWidth, -halfHeight, halfDepth), XMFLOAT3(0, 0, 1), m_Color)
			);

			//LEFT
			pMesh->AddQuad(
				VertexPosNormCol(XMFLOAT3(-halfWidth, halfHeight, halfDepth), XMFLOAT3(-1, 0, 0), m_Color),
				VertexPosNormCol(XMFLOAT3(-halfWidth, halfHeight, -halfDepth), XMFLOAT3(-1, 0, 0), m_Color),
				VertexPosNormCol(XMFLOAT3(-halfWidth, -halfHeight, -halfDepth), XMFLOAT3(-1, 0, 0), m_Color),
				VertexPosNormCol(XMFLOAT3(-halfWidth, -halfHeight, halfDepth), XMFLOAT3(-1, 0, 0), m_Color)
			);

			//RIGHT
			pMesh->AddQuad(
				VertexPosNormCol(XMFLOAT3(halfWidth, halfHeight, -halfDepth), XMFLOAT3(1, 0, 0), m_Color),
				VertexPosNormCol(XMFLOAT3(halfWidth, halfHeight, halfDepth), XMFLOAT3(1, 0, 0), m_Color),
				VertexPosNormCol(XMFLOAT3(halfWidth, -halfHeight, halfDepth), XMFLOAT3(1, 0, 0), m_Color),
				VertexPosNormCol(XMFLOAT3(halfWidth, -halfHeight, -halfDepth), XMFLOAT3(1, 0, 0), m_Color)
			);

			//TOP
			pMesh->AddQuad(
				VertexPosNormCol(XMFLOAT3(-halfWidth, halfHeight, halfDepth), XMFLOAT3(0, 1, 0), m_Color),
				VertexPosNormCol(XMFLOAT3(halfWidth, halfHeight, halfDepth), XMFLOAT3(0, 1, 0), m_Color),
				VertexPosNormCol(XMFLOAT3(halfWidth, halfHeight, -halfDepth), XMFLOAT3(0, 1, 0), m_Color),
				VertexPosNormCol(XMFLOAT3(-halfWidth, halfHeight, -halfDepth), XMFLOAT3(0, 1, 0), m_Color)
			);

			//BOTTOM
			pMesh->AddQuad(
				VertexPosNormCol(XMFLOAT3(-halfWidth, -halfHeight, -halfDepth), XMFLOAT3(0, -1, 0), m_Color),
				VertexPosNormCol(XMFLOAT3(halfWidth, -halfHeight, -halfDepth), XMFLOAT3(0, -1, 0), m_Color),
				VertexPosNormCol(XMFLOAT3(halfWidth, -halfHeight, halfDepth), XMFLOAT3(0, -1, 0), m_Color),
				VertexPosNormCol(XMFLOAT3(-halfWidth, -halfHeight, halfDepth), XMFLOAT3(0, -1, 0), m_Color)
			);

			AddComponent(pMesh);
		}
	}
}

void Bomb::Update(const SceneContext& sceneContext)
{
	m_CountdownTimer -= sceneContext.pGameTime->GetElapsed();
	if (m_CountdownTimer <= 0)
	{
		SoundManager::Get()->GetSystem()->playSound(m_pExplosionSound, nullptr, false, nullptr);
		Explode();
		if (m_pPlacer != nullptr)
			m_pPlacer->OnBombExplode(this);
		GetScene()->RemoveChild(this, true);
	}
}

void Bomb::Explode()
{
	ExplodeAt(m_pPosition->GetCoordinate());

	ExplodeInDirection(XMINT2{ 1, 0 }, m_ExplosionRadius);
	ExplodeInDirection(XMINT2{ 0, 1 }, m_ExplosionRadius);
	ExplodeInDirection(XMINT2{ -1, 0 }, m_ExplosionRadius);
	ExplodeInDirection(XMINT2{ 0, -1 }, m_ExplosionRadius);
}
void Bomb::ExplodeInDirection(const XMINT2& direction, int distance)
{
	XMINT2 explosionLocation{ m_pPosition->GetCoordinate() };
	for (int i = 0; i < distance; i++)
	{
		explosionLocation = explosionLocation + direction;

		// if unbreakable there, stop
		if (m_pMap->GetTypeAtCoordinate<UnbreakableBlock>(explosionLocation) != nullptr)
			return;

		// if breakable there, explode but don't go further
		// if bomb there, explode but don't go further
		bool shouldStopAfterExplosion = m_pMap->GetTypeAtCoordinate<BreakableBlock>(explosionLocation) != nullptr
			|| m_pMap->GetTypeAtCoordinate<Bomb>(explosionLocation) != nullptr;

		ExplodeAt(explosionLocation);

		if (shouldStopAfterExplosion)
			return; // we only want to stop AFTER we've exploded
	}
}
void Bomb::ExplodeAt(const XMINT2& location)
{
	// break block if there
	BreakableBlock* pBlock = m_pMap->GetTypeAtCoordinate<BreakableBlock>(location);
	if (pBlock != nullptr)
	{
		GetScene()->RemoveChild(pBlock, true);
	}
	// if player there, KILL
	Player* pPlayer = m_pMap->GetTypeAtCoordinate<Player>(location);
	if (pPlayer != nullptr)
	{
		pPlayer->Kill();
	}

	// spawn particle effect at location
	XMFLOAT3 pos = m_pMap->GetTilePositionAt(location);
	float tempy = pos.y;
	pos.y = pos.z;
	pos.z = tempy;
	BombExplosion* pExplosion = new BombExplosion(pos);
	GetScene()->AddChild(pExplosion);
}

#include "stdafx.h"
#include "BombPlacerComponent.h"
#include "Prefabs/Game/Bomb/Bomb.h"

BombPlacerComponent::BombPlacerComponent(int bombLimit, int explosionRadius)
	: m_BombLimit(bombLimit)
	, m_ExplosionRadius(explosionRadius)
{
}

void BombPlacerComponent::PlaceBomb()
{
	if (m_pCurrentBombs.size() >= m_BombLimit)
		return;

	if (m_pMap->GetTypeAtCoordinate<Bomb>(m_pMyCoordinate->GetCoordinate()) != nullptr)
		return;

	// spawn new bomb at my coordinate
	Bomb* pBomb = new Bomb(this, m_pMyCoordinate->GetCoordinate(), m_ExplosionRadius);
	GetScene()->AddChild(pBomb);
	m_pCurrentBombs.push_back(pBomb);
	SoundManager::Get()->GetSystem()->playSound(m_pPlaceSound, nullptr, false, nullptr);
}

void BombPlacerComponent::OnBombExplode(Bomb* pBomb)
{
	auto pos = std::find(m_pCurrentBombs.begin(), m_pCurrentBombs.end(), pBomb);
	if (pos != m_pCurrentBombs.end())
	{
		m_pCurrentBombs.erase(pos);
	}
}

void BombPlacerComponent::IncreaseBombLimit()
{
	m_BombLimit++;
}

void BombPlacerComponent::IncreaseExplosionRadius()
{
	m_ExplosionRadius++;
}

void BombPlacerComponent::Initialize(const SceneContext& /*sceneContext*/)
{
	m_pMyCoordinate = GetGameObject()->GetComponent<GridCoordinateComponent>();
	m_pMap = GetScene()->FindGameObjectWithTag(TileGridMap::m_TagName)->GetComponent<TileGridMap>();

	SoundManager::Get()->GetSystem()->createSound("Resources/Sounds/drop.wav", FMOD_DEFAULT, nullptr, &m_pPlaceSound);
}

void BombPlacerComponent::OnSceneDetach(GameScene* /*pScene*/)
{
	for (Bomb* pBomb : m_pCurrentBombs)
	{
		pBomb->PlayerDestroyed(this);
	}
}

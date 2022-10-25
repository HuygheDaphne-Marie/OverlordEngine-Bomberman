#include "stdafx.h"
#include "GridMovementComponent.h"
#include "Utils/MathUtils.h"

#include "Components/GridCoordinateComponent.h"
#include "Components/TileGridMap.h"
#include "Prefabs/Game/Tiles/MovementBlocker.h"

const float GridMovementComponent::m_MovementSpeedPickupPercentageModifier = 0.80f; // 20% decrease in movement duration

GridMovementComponent::GridMovementComponent(float movementDuration)
	: m_MovementDuration{movementDuration}
{
}

bool GridMovementComponent::IsMoving() const
{
	return m_MovementTimer > 0;
}

bool GridMovementComponent::MoveNorth()
{
	if (IsMoving())
		false;

	return Move(MoveDirection::North);
}
bool GridMovementComponent::MoveEast()
{
	if (IsMoving())
		false;

	return Move(MoveDirection::East);
}
bool GridMovementComponent::MoveSouth()
{
	if (IsMoving())
		false;

	return Move(MoveDirection::South);
}
bool GridMovementComponent::MoveWest()
{
	if (IsMoving())
		false;

	return Move(MoveDirection::West);
}
bool GridMovementComponent::Move(const MoveDirection& direction)
{
	if (IsMoving())
		false;

	XMINT2 delta{};
	switch (direction)
	{
	case MoveDirection::North:
		delta.y = 1;
		break;
	case MoveDirection::East:
		delta.x = 1;
		break;
	case MoveDirection::South:
		delta.y = -1;
		break;
	case MoveDirection::West:
	default: // should be impossible, but just so we never try to move to our own spot
		delta.x = -1;
		break;
	}

	return Move(delta);
}

void GridMovementComponent::IncreaseMovementSpeed()
{
	m_MovementDuration *= m_MovementSpeedPickupPercentageModifier;
}

bool GridMovementComponent::Move(const XMINT2& delta)
{
	if (IsMoving()) // should never need this but code safety
		return false;

	if (m_pMap == nullptr || m_pMyCoordinate == nullptr)
	{
		Logger::LogError(L"GridMovementComponent: Tried to move, but no Map or Coordinate component found!!");
		return false;
	}

	XMINT2 destination = m_pMyCoordinate->GetCoordinate() + delta;
	if (m_pMap->IsTileBlocked(destination))
		return false;

	// Set origin & destination, reset timer & put movementBlocker on destination
	m_Origin = m_pMyCoordinate->GetCoordinate();
	m_Destination = destination;
	m_MovementTimer = m_MovementDuration;
	m_pMyMovementBlocker->SetCoordinate(destination);

	SoundManager::Get()->GetSystem()->playSound(m_pWalkSound, nullptr, false, nullptr);

	return true;
}

void GridMovementComponent::Initialize(const SceneContext& /*sceneContext*/)
{
	GameObject* pTileMapGO = GetScene()->FindGameObjectWithTag(TileGridMap::m_TagName);
	if (pTileMapGO != nullptr)
	{
		m_pMap = pTileMapGO->GetComponent<TileGridMap>();
	}
	m_pMyCoordinate = GetGameObject()->GetComponent<GridCoordinateComponent>();

	// Set our transform to out grid coordinate
	GetTransform()->Translate(m_pMap->GetTilePositionAt(m_pMyCoordinate->GetCoordinate()));

	// Add movementBlocker to prevent people moving to our spot
	MovementBlocker* pMovementBlocker = new MovementBlocker(m_Destination); // destination starts at (0,0) which is unreachable anyway
	GetGameObject()->AddChild(pMovementBlocker);
	m_pMyMovementBlocker = pMovementBlocker->GetComponent<GridCoordinateComponent>();


	SoundManager::Get()->GetSystem()->createSound("Resources/Sounds/footstep.wav", FMOD_DEFAULT, nullptr, &m_pWalkSound);
}

void GridMovementComponent::Update(const SceneContext& sceneContext)
{
	if (IsMoving())
	{
		// Increment timer
		m_MovementTimer -= sceneContext.pGameTime->GetElapsed();

		// move towards destination pos
		const float linearT = 1 - (m_MovementTimer / m_MovementDuration);
		XMFLOAT3 newPos = Lerp(m_pMap->GetTilePositionAt(m_Origin), m_pMap->GetTilePositionAt(m_Destination), linearT);
		GetTransform()->Translate(newPos);
		
		// one timer is halfway, set grid coord to destination
		if (m_pMyCoordinate->GetCoordinate() != m_Destination && m_MovementTimer >= m_MovementDuration / 2)
		{
			m_pMyCoordinate->SetCoordinate(m_Destination);
		}

		if (!IsMoving()) // Have we stopped moving this frame?
		{
			m_Origin = m_Destination;
			GetTransform()->Translate(m_pMap->GetTilePositionAt(m_Destination)); // make sure we're on the exact right spot
		}
	}
}

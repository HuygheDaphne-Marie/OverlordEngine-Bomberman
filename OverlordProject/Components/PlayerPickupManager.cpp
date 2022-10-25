#include "stdafx.h"
#include "PlayerPickupManager.h"

#include "Prefabs/Game/Pickups/BombCountIncrease.h"
#include "Prefabs/Game/Pickups/ExplosionRadiusIncrease.h"
#include "Prefabs/Game/Pickups/MovementSpeedIncrease.h"

PlayerPickupManager::PlayerPickupManager(const PickupLimits& limits)
	: BaseComponent{}
	, m_Limits{limits}
{
}

void PlayerPickupManager::Initialize(const SceneContext& /*sceneContext*/)
{
	m_pPlacer = GetGameObject()->GetComponent<BombPlacerComponent>();
	m_pMovement = GetGameObject()->GetComponent<GridMovementComponent>();
}

bool PlayerPickupManager::OnBombIncrease(BombCountIncrease* pPickup)
{
	if (pPickup == nullptr || m_CurrentPickupCounts.BombLimit >= m_Limits.BombLimit)
		return false;

	m_CurrentPickupCounts.BombLimit++;
	m_pPlacer->IncreaseBombLimit();
	return true;
}

bool PlayerPickupManager::OnExplosionRadiusIncrease(ExplosionRadiusIncrease* pPickup)
{
	if (pPickup == nullptr || m_CurrentPickupCounts.RadiusLimit >= m_Limits.RadiusLimit)
		return false;

	m_CurrentPickupCounts.RadiusLimit++;
	m_pPlacer->IncreaseExplosionRadius();
	return true;
}

bool PlayerPickupManager::OnMovementSpeedIncrease(MovementSpeedIncrease* pPickup)
{
	if (pPickup == nullptr || m_CurrentPickupCounts.MovementSpeedLimit >= m_Limits.MovementSpeedLimit)
		return false;

	m_CurrentPickupCounts.MovementSpeedLimit++;
	m_pMovement->IncreaseMovementSpeed();
	return true;
}

const PlayerPickupManager::PickupLimits& PlayerPickupManager::GetCurrentPickupCounts() const
{
	return m_CurrentPickupCounts;
}

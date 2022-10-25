#include "stdafx.h"
#include "MovementSpeedIncrease.h"
#include "Components/GridMovementComponent.h"

MovementSpeedIncrease::MovementSpeedIncrease(const XMINT2& position)
	: BasePickup(position, L"Textures/items_movementSpeed.png")
{
}

bool MovementSpeedIncrease::OnPickup(Player* pPlayer)
{
	PlayerPickupManager* pPickupManager = pPlayer->GetComponent<PlayerPickupManager>();
	if (pPickupManager != nullptr)
	{
		return pPickupManager->OnMovementSpeedIncrease(this);
	}
	return false;
}

#include "stdafx.h"
#include "ExplosionRadiusIncrease.h"
#include "Components/BombPlacerComponent.h"

ExplosionRadiusIncrease::ExplosionRadiusIncrease(const XMINT2& position)
	: BasePickup(position, L"Textures/items_explosionRadius.png")
{
}

bool ExplosionRadiusIncrease::OnPickup(Player* pPlayer)
{
	PlayerPickupManager* pPickupManager = pPlayer->GetComponent<PlayerPickupManager>();
	if (pPickupManager != nullptr)
	{
		return pPickupManager->OnExplosionRadiusIncrease(this);
	}
	return false;
}

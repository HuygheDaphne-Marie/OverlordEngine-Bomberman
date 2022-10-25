#include "stdafx.h"
#include "BombCountIncrease.h"
#include "Components/BombPlacerComponent.h"

BombCountIncrease::BombCountIncrease(const XMINT2& position)
	: BasePickup{position, L"Textures/items_bombCount.png"}
{
}

bool BombCountIncrease::OnPickup(Player* pPlayer)
{
	PlayerPickupManager* pPickupManager = pPlayer->GetComponent<PlayerPickupManager>();
	if (pPickupManager != nullptr)
	{
		return pPickupManager->OnBombIncrease(this);
	}
	return false;
}

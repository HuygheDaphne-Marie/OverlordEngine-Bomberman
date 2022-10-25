#pragma once
#include "Prefabs/Game/Pickups/BasePickup.h"

class BombCountIncrease : public BasePickup
{
public:
	BombCountIncrease(const XMINT2& position);
	~BombCountIncrease() override = default;
	BombCountIncrease(const BombCountIncrease & other) = delete;
	BombCountIncrease(BombCountIncrease && other) noexcept = delete;
	BombCountIncrease& operator=(const BombCountIncrease & other) = delete;
	BombCountIncrease& operator=(BombCountIncrease && other) noexcept = delete;

protected:
	bool OnPickup(Player* pPlayer) override;
};


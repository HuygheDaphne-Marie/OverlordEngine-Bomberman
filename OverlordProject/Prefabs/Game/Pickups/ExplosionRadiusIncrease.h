#pragma once
#include "Prefabs/Game/Pickups/BasePickup.h"

class ExplosionRadiusIncrease : public BasePickup
{
public:
	ExplosionRadiusIncrease(const XMINT2& position);
	~ExplosionRadiusIncrease() override = default;
	ExplosionRadiusIncrease(const ExplosionRadiusIncrease & other) = delete;
	ExplosionRadiusIncrease(ExplosionRadiusIncrease && other) noexcept = delete;
	ExplosionRadiusIncrease& operator=(const ExplosionRadiusIncrease & other) = delete;
	ExplosionRadiusIncrease& operator=(ExplosionRadiusIncrease && other) noexcept = delete;

protected:
	bool OnPickup(Player * pPlayer) override;
};


#pragma once
#include "Prefabs/Game/Pickups/BasePickup.h"

class MovementSpeedIncrease : public BasePickup
{
public:
	MovementSpeedIncrease(const XMINT2& position);
	~MovementSpeedIncrease() override = default;
	MovementSpeedIncrease(const MovementSpeedIncrease & other) = delete;
	MovementSpeedIncrease(MovementSpeedIncrease && other) noexcept = delete;
	MovementSpeedIncrease& operator=(const MovementSpeedIncrease & other) = delete;
	MovementSpeedIncrease& operator=(MovementSpeedIncrease && other) noexcept = delete;

protected:
	bool OnPickup(Player* pPlayer) override;
};


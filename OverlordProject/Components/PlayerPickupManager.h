#pragma once
#include "..\OverlordEngine\Components\BaseComponent.h"

#include "Components/BombPlacerComponent.h"
#include "Components/GridMovementComponent.h"

class BombCountIncrease;
class ExplosionRadiusIncrease;
class MovementSpeedIncrease;

class PlayerPickupManager : public BaseComponent
{
public:
	struct PickupLimits // How many of each type of pickup can be picked up
	{
		int BombLimit{};
		int RadiusLimit{};
		int MovementSpeedLimit{};

		
	};

	PlayerPickupManager(const PickupLimits& limits);
	~PlayerPickupManager() override = default;
	PlayerPickupManager(const PlayerPickupManager& other) = delete;
	PlayerPickupManager(PlayerPickupManager&& other) noexcept = delete;
	PlayerPickupManager& operator=(const PlayerPickupManager& other) = delete;
	PlayerPickupManager& operator=(PlayerPickupManager&& other) noexcept = delete;

	bool OnBombIncrease(BombCountIncrease* pPickup);
	bool OnExplosionRadiusIncrease(ExplosionRadiusIncrease* pPickup);
	bool OnMovementSpeedIncrease(MovementSpeedIncrease* pPickup);

	const PickupLimits& GetCurrentPickupCounts() const;

protected:
	const PickupLimits m_Limits{};
	PickupLimits m_CurrentPickupCounts{};

	BombPlacerComponent* m_pPlacer{};
	GridMovementComponent* m_pMovement{};

	void Initialize(const SceneContext& sceneContext) override;
};

inline bool operator==(const PlayerPickupManager::PickupLimits& a, const PlayerPickupManager::PickupLimits& b)
{
	return a.BombLimit == b.BombLimit && a.MovementSpeedLimit == b.MovementSpeedLimit && a.RadiusLimit == b.RadiusLimit;
}

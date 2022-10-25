#pragma once
#include "..\OverlordEngine\Scenegraph\GameObject.h"

class BasePickup;
class BreakableBlock;

class SpawnManager : public GameObject
{
public:
	static const std::wstring m_Tag;

	SpawnManager(float spawnChance);
	~SpawnManager() override = default;
	SpawnManager(const SpawnManager& other) = delete;
	SpawnManager(SpawnManager&& other) noexcept = delete;
	SpawnManager& operator=(const SpawnManager& other) = delete;
	SpawnManager& operator=(SpawnManager&& other) noexcept = delete;

	void OnBreakableBlockDestroyed(BreakableBlock* pBlock);

protected:
	void Initialize(const SceneContext&) override;

private:
	enum class PickupTypes
	{
		BombCount,
		ExplosionRadius,
		MovementSpeed,
		LAST
	};
	float m_SpawnChance{};
};


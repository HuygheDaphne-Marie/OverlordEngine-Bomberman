#include "stdafx.h"
#include "SpawnManager.h"
#include "Prefabs/Game/Tiles/BreakableBlock.h"

#include "Prefabs/Game/Pickups/BombCountIncrease.h"
#include "Prefabs/Game/Pickups/ExplosionRadiusIncrease.h"
#include "Prefabs/Game/Pickups/MovementSpeedIncrease.h"

const std::wstring SpawnManager::m_Tag{ L"SpawnManager" };

SpawnManager::SpawnManager(float spawnChance)
	: GameObject()
	, m_SpawnChance(spawnChance)
{
}

void SpawnManager::OnBreakableBlockDestroyed(BreakableBlock* pBlock)
{
	float spawnRoll = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // 0.0f -> 1.0f (inclusive)
	if (spawnRoll < m_SpawnChance)
	{
		// get block pos
		const XMINT2 blockPos = pBlock->GetComponent<GridCoordinateComponent>()->GetCoordinate();

		int randomIndex = rand() % static_cast<int>(PickupTypes::LAST);
		PickupTypes typeToSpawn = static_cast<PickupTypes>(randomIndex);

		BasePickup* pNewPickup = nullptr;
		switch (typeToSpawn)
		{
		case PickupTypes::BombCount:
			pNewPickup = new BombCountIncrease(blockPos);
			break;
		case PickupTypes::ExplosionRadius:
			pNewPickup = new ExplosionRadiusIncrease(blockPos);
			break;
		case PickupTypes::MovementSpeed:
			pNewPickup = new MovementSpeedIncrease(blockPos);
			break;
		default:
			Logger::LogError(L"SpawnManager: default got reached in spawn switch case! A type of pickup is unaccounted for or LAST got selected!!");
			break;
		}

		if (pNewPickup != nullptr)
		{
			GetScene()->AddChild(pNewPickup);
		}
	}
}

void SpawnManager::Initialize(const SceneContext&)
{
	GameObject* pOtherSpawnManager = GetScene()->FindGameObjectWithTag(m_Tag);
	if (pOtherSpawnManager != nullptr)
	{
		GetScene()->RemoveChild(this, true);
	}
	else
	{
		SetTag(m_Tag);
	}
}

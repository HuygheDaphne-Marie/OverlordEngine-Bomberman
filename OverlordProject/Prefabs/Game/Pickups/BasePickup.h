#pragma once
#include "Prefabs/Game/Tiles/TileEntity.h"
#include "Prefabs/Game/Player/Player.h"
#include "Components/PlayerPickupManager.h"
/*
- Make Pickup Base GO
- should have collider (trigger) which checks for collisions with player
- when a collision happens with a player
	- call pure virtual OnPickup function
		- defined later in derived pickups
		- delete self after pickup happens
*/

class BasePickup : public TileEntity
{
public:
	BasePickup(const XMINT2& position, const std::wstring& texturePath= L"Textures/items.png");
	~BasePickup() override = default;
	BasePickup(const BasePickup & other) = delete;
	BasePickup(BasePickup && other) noexcept = delete;
	BasePickup& operator=(const BasePickup & other) = delete;
	BasePickup& operator=(BasePickup && other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;
	virtual bool OnPickup(Player* pPlayer) = 0;

private:
	GridCoordinateComponent* m_pPosition{};
	TileGridMap* m_pMap{};
	FMOD::Sound* m_pPickupSound{};

	bool m_HasBeenPickedUp{ false };
	const std::wstring m_TexturePath{};

	void PickupOnTrigger(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action);
};


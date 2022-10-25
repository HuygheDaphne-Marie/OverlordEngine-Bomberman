#include "stdafx.h"
#include "BasePickup.h"
#include "Materials/DiffuseMaterial.h"


BasePickup::BasePickup(const XMINT2& position, const std::wstring& texturePath)
	: TileEntity{ position.x, position.y }
	, m_TexturePath{ texturePath }
{
}

void BasePickup::Initialize(const SceneContext& sceneContext)
{
	TileEntity::Initialize(sceneContext);

	m_pMap = GetScene()->FindGameObjectWithTag(TileGridMap::m_TagName)->GetComponent<TileGridMap>();
	m_pPosition = GetComponent<GridCoordinateComponent>();

	XMFLOAT3 spawnPos{ m_pMap->GetTilePositionAt(m_pPosition->GetCoordinate()) };
	spawnPos.z += m_pMap->m_TileSize / 3;

	GetTransform()->Translate(spawnPos);
	GetTransform()->Rotate(-45.0f, 0.0f, 0.0f);
	GetTransform()->Scale(-1.0f, 1.0f, 1.0f);

	// Setup Model
	DiffuseMaterial* pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	pMaterial->SetDiffuseTexture(m_TexturePath);

	ModelComponent* pModelComp = AddComponent(new ModelComponent(L"Meshes/Pickup.ovm"));
	pModelComp->SetMaterial(pMaterial);

	// Setup Trigger
	// Make Material
	auto& physX = PxGetPhysics();
	const auto pDefaultMaterial = physX.createMaterial(0.0f, 0.0f, 0.0f);

	// Make RB (using model shape)
	RigidBodyComponent* pickupTrigger = AddComponent(new RigidBodyComponent);
	pickupTrigger->SetKinematic(true);

	const float quaterSize = m_pMap->m_TileSize / 4.f;
	pickupTrigger->AddCollider(PxBoxGeometry{ quaterSize, quaterSize, quaterSize }, *pDefaultMaterial, true);

	// Setup Trigger callback
	PhysicsCallback triggerCallBack =
		std::bind(
			&BasePickup::PickupOnTrigger, this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3
		);
	SetOnTriggerCallBack(triggerCallBack);

	SoundManager::Get()->GetSystem()->createSound("Resources/Sounds/pickup.wav", FMOD_DEFAULT, nullptr, &m_pPickupSound);
}

void BasePickup::Update(const SceneContext& /*sceneContext*/)
{
	if (m_HasBeenPickedUp)
	{
		GetScene()->RemoveChild(this, true);
	}
}

void BasePickup::PickupOnTrigger(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action)
{
	if (pTriggerObject != this || action != PxTriggerAction::ENTER)
		return;

	Player* pPlayer = dynamic_cast<Player*>(pOtherObject);
	if (pPlayer == nullptr)
		return;

	m_HasBeenPickedUp = OnPickup(pPlayer);
	if (m_HasBeenPickedUp)
		SoundManager::Get()->GetSystem()->playSound(m_pPickupSound, nullptr, false, nullptr);
}

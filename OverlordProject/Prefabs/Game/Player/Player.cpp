#include "stdafx.h"
#include "Player.h"

#include "Materials/Shadow/DiffuseMaterial_Shadow_Skinned.h"
#include "Materials/DiffuseMaterial_Skinned.h"

#include "Components/PlayerPickupManager.h"
#include "Prefabs/Game/Managers/GameManager.h"
#include "Prefabs/Game/UI/PlayerUI.h"

const std::wstring Player::m_TagName{L"Player"};

Player::Player(const XMINT2& coordinate, const CharacterInputComponent::InputDesc& inputActions)
	: TileEntity(coordinate.x, coordinate.y)
	, m_InputActions{inputActions}
{
}

void Player::Kill()
{
	GetScene()->RemoveChild(this, true);
}

void Player::SetPlayerUI(PlayerUI* pUI)
{
	m_pMyUI = pUI;
}

void Player::SetPlayerNumber(int playerNumber)
{
	if (m_PlayerNumber == -1 && playerNumber > 0)
		m_PlayerNumber = playerNumber;
}

int Player::GetPlayerNumber() const
{
	return m_PlayerNumber;
}

void Player::Initialize(const SceneContext& sceneContext)
{
	TileEntity::Initialize(sceneContext);

	SetTag(m_TagName);

	GridMovementComponent* pMovement = AddComponent(new GridMovementComponent(0.25f));
	BombPlacerComponent* pBombPlacer = AddComponent(new BombPlacerComponent());
	AddComponent(new CharacterInputComponent(m_InputActions, pMovement, pBombPlacer));

	PlayerPickupManager::PickupLimits limits{};
	limits.BombLimit = 3; // total of 4 bombs
	limits.RadiusLimit = 5; // total of 6 tile range
	limits.MovementSpeedLimit = 3;
	AddComponent(new PlayerPickupManager(limits));

	// Setup Collider
	auto& physX = PxGetPhysics();
	const auto pDefaultMaterial = physX.createMaterial(0.0f, 0.0f, 0.0f);

	// Make RB (using model shape)
	RigidBodyComponent* playerRb = AddComponent(new RigidBodyComponent);
	playerRb->SetKinematic(true);

	const float halfWidth = 0.5f / 2.f;
	const float halfHeight = 1.0f / 2.f;
	const float halfDepth = 0.5f / 2.f;
	playerRb->AddCollider(PxBoxGeometry{halfWidth, halfHeight, halfDepth}, *pDefaultMaterial);
	
#if NDEBUG
	const bool castShadows = true;
	const auto pSkinnedMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow_Skinned>(); // no shadows in debug
#else
	const bool castShadows = false;
	const auto pSkinnedMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
#endif
	pSkinnedMaterial->SetDiffuseTexture(L"Textures/Character_diffuse.png");
	const auto pModel = AddComponent(new ModelComponent(L"Meshes/Character.ovm", castShadows));
	pModel->SetMaterial(pSkinnedMaterial);
	GetTransform()->Scale(0.01f);

	m_pAnimator = pModel->GetAnimator();
	m_pAnimator->SetAnimation(m_CurrentAnimationClipId);
	m_pAnimator->SetAnimationSpeed(m_CurrentAnimationSpeed);
#if NDEBUG
	m_pAnimator->Play(); // idle animation for some reason takes a lot during debug, so it's disabled
#endif

	m_pMover = GetComponent<GridMovementComponent>();
}

void Player::Update(const SceneContext& /*sceneContext*/)
{
	if (m_pMover != nullptr)
	{
		AnimationIds previousAnimationId = m_CurrentAnimationClipId;

		if (m_pMover->IsMoving())
			m_CurrentAnimationClipId = AnimationIds::run;
		else
			m_CurrentAnimationClipId = AnimationIds::idle2;

		if (m_CurrentAnimationClipId != previousAnimationId)
			m_pAnimator->SetAnimation(m_CurrentAnimationClipId);		
	}
}

void Player::OnSceneDetach(GameScene* pScene)
{
	// Notify GameManager of our demise
	GameManager* pGameManager{};
	pGameManager = dynamic_cast<GameManager*>(pScene->FindGameObjectWithTag(GameManager::m_TagName));
	if (pGameManager != nullptr)
		pGameManager->OnPlayerDied(this);

	// And out UI too
	if (m_pMyUI != nullptr)
		m_pMyUI->SetBoundPlayer(nullptr);
}

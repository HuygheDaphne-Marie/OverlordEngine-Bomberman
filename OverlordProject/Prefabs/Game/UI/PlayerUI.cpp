#include "stdafx.h"
#include "PlayerUI.h"
#include "Prefabs/Game/Player/Player.h"
#include "Prefabs/Game/UI/SpriteList.h"

const int PlayerUI::m_SpriteStep{ 80 };
const std::wstring PlayerUI::m_BombIncreaseSprite{ L"Textures/bombIcon.png" };
const std::wstring PlayerUI::m_RadiusIncreaseSprite{ L"Textures/FireIcon.png" };
const std::wstring PlayerUI::m_MovementSpeedSprite{ L"Textures/SkateIcon.png" };

PlayerUI::PlayerUI(Player* pBoundPlayer, const XMFLOAT2& pos, bool alignDown, bool alignLeft)
	: GameObject()
	, m_pBoundPlayer(pBoundPlayer)
	, m_Pos(pos)
	, m_AlignDown(alignDown)
	, m_AlignLeft(alignLeft)
{
}

void PlayerUI::SetBoundPlayer(Player* pPlayer)
{
	m_pBoundPlayer = pPlayer;
}

void PlayerUI::Initialize(const SceneContext& /*sceneContext*/)
{
	if (m_pBoundPlayer != nullptr)
		m_pBoundPlayer->SetPlayerUI(this);

	// get the pickupmanager
	m_pBoundPickupManager = m_pBoundPlayer->GetComponent<PlayerPickupManager>();
	
	GetTransform()->Translate(m_Pos.x, m_Pos.y, 1.f);

	// Make the sprite lists
	const int listStep = (m_AlignDown) ? m_SpriteStep : -m_SpriteStep;
	const int spriteStep = (m_AlignLeft) ? m_SpriteStep : -m_SpriteStep;

	XMFLOAT3 listPos{ GetTransform()->GetPosition() };
	SpriteList* spriteList = new SpriteList(m_BombIncreaseSprite, spriteStep);
	m_pDisplayedPickups.emplace(m_BombIncreaseSprite, spriteList);
	m_pDisplayedPickups.at(m_BombIncreaseSprite)->GetTransform()->Translate(listPos);
	AddChild(spriteList);

	listPos.y += listStep;
	spriteList = new SpriteList(m_RadiusIncreaseSprite, spriteStep);
	m_pDisplayedPickups.emplace(m_RadiusIncreaseSprite, spriteList);
	m_pDisplayedPickups.at(m_RadiusIncreaseSprite)->GetTransform()->Translate(listPos);
	AddChild(spriteList);

	listPos.y += listStep;
	spriteList = new SpriteList(m_MovementSpeedSprite, spriteStep);
	m_pDisplayedPickups.emplace(m_MovementSpeedSprite, spriteList);
	m_pDisplayedPickups.at(m_MovementSpeedSprite)->GetTransform()->Translate(listPos);
	AddChild(spriteList);
}

void PlayerUI::Update(const SceneContext& /*sceneContext*/)
{
	if (m_pBoundPlayer == nullptr)
	{
		GetScene()->RemoveChild(this, true);
		return;
	}

	// check if values have changed compared to displayed values
	if (GetDisplayedCounts() != m_pBoundPickupManager->GetCurrentPickupCounts())
		UpdateDisplayedPickups();
}

void PlayerUI::UpdateDisplayedPickups()
{
	const PlayerPickupManager::PickupLimits targetCounts{ m_pBoundPickupManager->GetCurrentPickupCounts() };
	UpdateDisplayedPickupsOfType(m_BombIncreaseSprite, targetCounts.BombLimit);
	UpdateDisplayedPickupsOfType(m_RadiusIncreaseSprite, targetCounts.RadiusLimit);
	UpdateDisplayedPickupsOfType(m_MovementSpeedSprite, targetCounts.MovementSpeedLimit);
}

const PlayerPickupManager::PickupLimits PlayerUI::GetDisplayedCounts() const
{
	PlayerPickupManager::PickupLimits limits{};
	limits.BombLimit = m_pDisplayedPickups.at(m_BombIncreaseSprite)->GetSpriteCount();
	limits.RadiusLimit = m_pDisplayedPickups.at(m_RadiusIncreaseSprite)->GetSpriteCount();
	limits.MovementSpeedLimit = m_pDisplayedPickups.at(m_MovementSpeedSprite)->GetSpriteCount();
	return limits;
}

void PlayerUI::UpdateDisplayedPickupsOfType(const std::wstring& spirte, int targetCount)
{
	SpriteList* sprites{ m_pDisplayedPickups.at(spirte) };
	const int currentCount{ sprites->GetSpriteCount() };

	if (currentCount == targetCount)
		return;
	else if (currentCount > targetCount)
	{
		for (size_t i = currentCount - 1; i >= targetCount; i--)
		{
			sprites->RemoveSprite();
		}
	}
	else
	{
		for (size_t i = currentCount; i < targetCount; i++)
		{
			sprites->AddSprite();
		}
	}
}

#include "stdafx.h"
#include "TimerUI.h"
#include "Prefabs/Game/Managers/GameManager.h"

TimerUI::TimerUI(GameManager* pGameManager)
	: GameObject()
	, m_pGameManager(pGameManager)
{
}

void TimerUI::Initialize(const SceneContext& sceneContext)
{
	m_pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/Bomberman_64.fnt");
	m_Pos.x = sceneContext.windowWidth / 2 - 50.f;
	m_Pos.y = 50.f;
}

void TimerUI::Update(const SceneContext& /*sceneContext*/)
{
	if (m_pGameManager != nullptr)
	{
		const std::string text = std::to_string(static_cast<int>(m_pGameManager->GetRemainingRoundTime()));
		TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(text), m_Pos, XMFLOAT4{Colors::White});
	}
}

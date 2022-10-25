#include "stdafx.h"
#include "GameEndScreen.h"

#include "Prefabs/Game/Player/Player.h"
#include "Prefabs/Game/UI/UISprite.h"
#include "Prefabs/Game/UI/Buttons/QuitButton.h"
#include "Prefabs/Game/UI/Buttons/RestartButton.h"
#include "Prefabs/Game/Managers/UIInputManager.h"

GameEndScreen::GameEndScreen(Player* pWinner)
	: GameObject()
	, m_pWinner{pWinner}
{
}

void GameEndScreen::Initialize(const SceneContext& sceneContext)
{
	GameScene* pScene = GetScene();

	UISprite* pBackground = new UISprite(L"Textures/shade.png", XMFLOAT2{ sceneContext.windowWidth / 2, sceneContext.windowHeight / 2 });
	pScene->AddChild(pBackground);

	m_EndText = (m_pWinner == nullptr) ? "DRAW" : "PLAYER " + std::to_string(m_pWinner->GetPlayerNumber()) + " WINS";
	m_pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/Bomberman_64.fnt");
	m_MenuX = sceneContext.windowWidth / 2 - 100.f;


	Button* pRestartBtn = new RestartButton(m_pFont, "RESTART", XMFLOAT2{ m_MenuX, sceneContext.windowHeight / 2 });
	pScene->AddChild(pRestartBtn);

	Button* pQuitBtn = new QuitButton(m_pFont, "QUIT", XMFLOAT2{ m_MenuX, sceneContext.windowHeight / 2 + 100.f });
	pScene->AddChild(pQuitBtn);

	// Relations
	pRestartBtn->m_Up = pQuitBtn;
	pRestartBtn->m_Down = pQuitBtn;

	pQuitBtn->m_Up = pRestartBtn;
	pQuitBtn->m_Down = pRestartBtn;

	UIInputManager* pUIInput = new UIInputManager(pRestartBtn);
	pScene->AddChild(pUIInput);
	pUIInput->RegisterButton(pQuitBtn);
	
	pUIInput->BindInput();
}

void GameEndScreen::Update(const SceneContext& sceneContext)
{
	TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(m_EndText), XMFLOAT2{ m_MenuX, sceneContext.windowHeight / 2 - 200.f }, XMFLOAT4{ Colors::White });
}

#include "stdafx.h"
#include "MainMenuScene.h"
#include "Prefabs/Game/UI/UISprite.h"
#include "Prefabs/Game/UI/Button.h"
#include "Prefabs/Game/UI/Buttons/QuitButton.h"
#include "Prefabs/Game/UI/Buttons/StartButton.h"

void MainMenuScene::Initialize()
{
#if NDEBUG
	GetSceneSettings().showInfoOverlay = false;
#endif

	const SceneContext& sceneContext{ GetSceneContext() };
	UISprite* pBackground = new UISprite(L"Textures/background.png", XMFLOAT2{ sceneContext.windowWidth / 2, sceneContext.windowHeight / 2 });
	AddChild(pBackground);

	m_pMenuFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/Bomberman_64.fnt");

	Button* pStartBtn = new StartButton(m_pMenuFont, "START", XMFLOAT2{ m_MenuPosX, 350.f });
	AddChild(pStartBtn);
	pStartBtn->SetSelectionZone(XMFLOAT2{ 264, 64 });

	Button* pQuitBtn = new QuitButton(m_pMenuFont, "QUIT", XMFLOAT2{ m_MenuPosX, 450.f });
	AddChild(pQuitBtn);

	// setup relations
	pStartBtn->m_Up = pQuitBtn;
	pStartBtn->m_Down = pQuitBtn;

	pQuitBtn->m_Up = pStartBtn;
	pQuitBtn->m_Down = pStartBtn;

	m_pUIInputManager = new UIInputManager(pStartBtn);
	AddChild(m_pUIInputManager);
	m_pUIInputManager->RegisterButton(pQuitBtn);
}

void MainMenuScene::OnSceneActivated()
{
	m_pUIInputManager->BindInput();
}

void MainMenuScene::OnSceneDeactivated()
{
	m_pUIInputManager->UnbindInput();
}

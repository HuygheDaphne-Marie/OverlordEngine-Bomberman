#include "stdafx.h"
#include "RestartButton.h"
#include "Scenes/Game/BombermanLevelScene.h"

RestartButton::RestartButton(SpriteFont* pFont, const std::string& text, const XMFLOAT2& pos)
	: Button(pFont, text, pos)
{
}

void RestartButton::OnPress()
{
	SceneManager::Get()->RemoveGameScene(SceneManager::Get()->GetActiveScene());
	SceneManager::Get()->AddGameScene(new BombermanLevelScene{});
	SceneManager::Get()->SetActiveGameScene(L"BombermanLevelScene");
}

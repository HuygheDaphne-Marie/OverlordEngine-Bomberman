#include "stdafx.h"
#include "StartButton.h"

StartButton::StartButton(SpriteFont* pFont, const std::string& text, const XMFLOAT2& pos)
	: Button(pFont, text, pos)
{
}

void StartButton::OnPress()
{
	SceneManager::Get()->SetActiveGameScene(L"BombermanLevelScene");
}

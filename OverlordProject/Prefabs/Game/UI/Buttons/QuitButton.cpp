#include "stdafx.h"
#include "QuitButton.h"

QuitButton::QuitButton(SpriteFont* pFont, const std::string& text, const XMFLOAT2& pos)
	: Button(pFont, text, pos)
{
}

void QuitButton::OnPress()
{
	PostQuitMessage(WM_QUIT);
}


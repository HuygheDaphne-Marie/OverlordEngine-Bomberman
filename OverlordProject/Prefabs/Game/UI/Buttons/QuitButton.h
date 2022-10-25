#pragma once
#include "../Button.h"

class QuitButton : public Button
{
public:
	QuitButton(SpriteFont* pFont, const std::string& text, const XMFLOAT2& pos);
	~QuitButton() override = default;
	QuitButton(const QuitButton & other) = delete;
	QuitButton(QuitButton && other) noexcept = delete;
	QuitButton& operator=(const QuitButton & other) = delete;
	QuitButton& operator=(QuitButton && other) noexcept = delete;

	void OnPress() override;
};


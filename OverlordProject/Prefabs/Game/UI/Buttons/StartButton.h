#pragma once
#include "../Button.h"

class StartButton : public Button
{
public:
	StartButton(SpriteFont* pFont, const std::string& text, const XMFLOAT2& pos);
	~StartButton() override = default;
	StartButton(const StartButton& other) = delete;
	StartButton(StartButton&& other) noexcept = delete;
	StartButton& operator=(const StartButton& other) = delete;
	StartButton& operator=(StartButton&& other) noexcept = delete;

	void OnPress() override;
};


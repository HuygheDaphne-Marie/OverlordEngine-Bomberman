#pragma once
#include "../Button.h"

class RestartButton : public Button
{
public:
	RestartButton(SpriteFont* pFont, const std::string& text, const XMFLOAT2& pos);
	~RestartButton() override = default;
	RestartButton(const RestartButton& other) = delete;
	RestartButton(RestartButton&& other) noexcept = delete;
	RestartButton& operator=(const RestartButton& other) = delete;
	RestartButton& operator=(RestartButton&& other) noexcept = delete;

	void OnPress() override;
};


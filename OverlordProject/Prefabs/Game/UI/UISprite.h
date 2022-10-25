#pragma once
#include "..\OverlordEngine\Scenegraph\GameObject.h"

class UISprite : public GameObject
{
public:
	UISprite(const std::wstring& spriteTexture, const XMFLOAT2& pos, float depth = 0.9f);
	~UISprite() override = default;
	UISprite(const UISprite& other) = delete;
	UISprite(UISprite&& other) noexcept = delete;
	UISprite& operator=(const UISprite& other) = delete;
	UISprite& operator=(UISprite&& other) noexcept = delete;

	const std::wstring& GetDisplayedSprite() const;

protected:
	void Initialize(const SceneContext& sceneContext) override;

private:
	const std::wstring m_SpritePath{};
	const XMFLOAT2 m_Pos{};
	const float m_Depth{};
};


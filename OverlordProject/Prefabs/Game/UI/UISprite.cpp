#include "stdafx.h"
#include "UISprite.h"

UISprite::UISprite(const std::wstring& spriteTexture, const XMFLOAT2& pos, float depth)
	: GameObject()
	, m_SpritePath(spriteTexture)
	, m_Pos(pos)
	, m_Depth(depth)
{
}

const std::wstring& UISprite::GetDisplayedSprite() const
{
	return m_SpritePath;
}

void UISprite::Initialize(const SceneContext& /*sceneContext*/)
{
	AddComponent(new SpriteComponent(m_SpritePath, { 0.5f,0.5f }, { 1.f,1.f,1.f,1.f }));
	GetTransform()->Translate(m_Pos.x, m_Pos.y, m_Depth);
}

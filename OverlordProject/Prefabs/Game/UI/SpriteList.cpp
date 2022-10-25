#include "stdafx.h"
#include "SpriteList.h"
#include "Prefabs/Game/UI/UISprite.h"

SpriteList::SpriteList(const std::wstring& spritesTexture, int spriteStep)
	: GameObject()
	, m_SpritesTexture{spritesTexture}
	, m_SpriteStep{spriteStep}
{
}

void SpriteList::Initialize(const SceneContext& /*sceneContext*/)
{
}

const int SpriteList::GetSpriteCount() const
{
	return static_cast<int>(m_pSprites.size());
}

void SpriteList::AddSprite()
{
	XMFLOAT3 pos = GetTransform()->GetPosition();
	if (!m_pSprites.empty())
	{
		pos = m_pSprites[m_pSprites.size() - 1]->GetTransform()->GetPosition();
		pos.x += m_SpriteStep;
	}

	UISprite* pNewSprite = new UISprite(m_SpritesTexture, XMFLOAT2{ pos.x, pos.y });
	AddChild(pNewSprite);
	m_pSprites.push_back(pNewSprite);
}

void SpriteList::RemoveSprite()
{
	if (m_pSprites.empty())
		return;

	RemoveChild(m_pSprites[m_pSprites.size() - 1], true);
	m_pSprites.pop_back();
}

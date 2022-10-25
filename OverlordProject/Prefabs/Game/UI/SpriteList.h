#pragma once
#include "..\OverlordEngine\Scenegraph\GameObject.h"

class SpriteList : public GameObject
{
public:
	SpriteList(const std::wstring& spritesTexture, int spriteStep);
	~SpriteList() override = default;
	SpriteList(const SpriteList& other) = delete;
	SpriteList(SpriteList&& other) noexcept = delete;
	SpriteList& operator=(const SpriteList& other) = delete;
	SpriteList& operator=(SpriteList&& other) noexcept = delete;

	const int GetSpriteCount() const;

	void AddSprite();
	void RemoveSprite();

protected:
	void Initialize(const SceneContext& sceneContext) override;

private:
	const std::wstring m_SpritesTexture{};
	const int m_SpriteStep{};
	std::vector<GameObject*> m_pSprites{};
};


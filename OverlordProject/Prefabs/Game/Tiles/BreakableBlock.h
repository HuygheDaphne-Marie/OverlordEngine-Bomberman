#pragma once
#include "Block.h"

// This acts more as a prefab variant than anything else, it's just meant to be a different preset
class BreakableBlock : public Block
{
public:
	BreakableBlock(const XMINT2& coordinate);
	~BreakableBlock() override = default;

	BreakableBlock(const BreakableBlock & other) = delete;
	BreakableBlock(BreakableBlock && other) noexcept = delete;
	BreakableBlock& operator=(const BreakableBlock & other) = delete;
	BreakableBlock& operator=(BreakableBlock && other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void OnSceneDetach(GameScene* pScene) override;

private:
	const static std::wstring m_BlockTexture;
};


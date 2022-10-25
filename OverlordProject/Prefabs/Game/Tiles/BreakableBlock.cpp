#include "stdafx.h"
#include "BreakableBlock.h"
#include "Prefabs/Game/Managers/SpawnManager.h"

const std::wstring BreakableBlock::m_BlockTexture{ L"Textures/block.png" };

BreakableBlock::BreakableBlock(const XMINT2& coordinate)
	: Block(coordinate, XMFLOAT3{ 0.75f, 1.0f , 0.75f }, m_BlockTexture)
{
}

void BreakableBlock::Initialize(const SceneContext& sceneContext)
{
	Block::Initialize(sceneContext);
}

void BreakableBlock::OnSceneDetach(GameScene* pScene)
{
	SpawnManager* pSpawnManager = dynamic_cast<SpawnManager*>(pScene->FindGameObjectWithTag(SpawnManager::m_Tag));
	if (pSpawnManager != nullptr)
	{
		pSpawnManager->OnBreakableBlockDestroyed(this);
	}
}

#include "stdafx.h"
#include "TileEntity.h"

TileEntity::TileEntity(int x, int y)
{
	AddComponent(new GridCoordinateComponent(x, y));
}

void TileEntity::Initialize(const SceneContext& /*sceneContext*/)
{
}

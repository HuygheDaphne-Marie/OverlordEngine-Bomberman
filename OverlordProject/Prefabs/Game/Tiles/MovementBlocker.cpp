#include "stdafx.h"
#include "MovementBlocker.h"

MovementBlocker::MovementBlocker(const XMINT2& coordinate)
	: TileEntity(coordinate.x, coordinate.y)
{
}

void MovementBlocker::Initialize(const SceneContext&)
{
	GetComponent<GridCoordinateComponent>()->SetIsBlocking(true);
}

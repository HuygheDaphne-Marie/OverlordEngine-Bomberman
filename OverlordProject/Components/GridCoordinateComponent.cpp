#include "stdafx.h"
#include "GridCoordinateComponent.h"

#include "TileGridMap.h"

GridCoordinateComponent::GridCoordinateComponent(const XMINT2& coordinate, bool isBlocking)
	: GridCoordinateComponent(coordinate.x, coordinate.y, isBlocking)
{
}
GridCoordinateComponent::GridCoordinateComponent(int x, int y, bool isBlocking)
	: m_Coordinate(x, y)
	, m_IsBlocking(isBlocking)
{
}

const XMINT2& GridCoordinateComponent::GetCoordinate() const
{
	return m_Coordinate;
}
void GridCoordinateComponent::SetCoordinate(const XMINT2& coordinate)
{
	m_Coordinate = coordinate;
}
void GridCoordinateComponent::SetCoordinate(int x, int y)
{
	m_Coordinate.x = x;
	m_Coordinate.y = y;
}

bool GridCoordinateComponent::GetIsBlocking() const
{
	return m_IsBlocking;
}
void GridCoordinateComponent::SetIsBlocking(bool isBlocking)
{
	m_IsBlocking = isBlocking;
}

void GridCoordinateComponent::Initialize(const SceneContext& /*sceneContext*/)
{
}

void GridCoordinateComponent::OnSceneAttach(GameScene* pScene)
{
	GameObject* pTileMap = pScene->FindGameObjectWithTag(L"TileMap");
	if (pTileMap != nullptr)
	{
		TileGridMap* pTileGridMap = pTileMap->GetComponent<TileGridMap>();
		if (pTileGridMap != nullptr)
		{
			pTileGridMap->AddTileEntity(this);
		}
	}
}

void GridCoordinateComponent::OnSceneDetach(GameScene* pScene)
{
	GameObject* pTileMap = pScene->FindGameObjectWithTag(L"TileMap");
	if (pTileMap != nullptr)
	{
		TileGridMap* pTileGridMap = pTileMap->GetComponent<TileGridMap>();
		if (pTileGridMap != nullptr)
		{
			pTileGridMap->RemoveTileEntity(this);
		}
	}
}

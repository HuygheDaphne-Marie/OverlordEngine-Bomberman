#include "stdafx.h"
#include "TileGridMap.h"
#include "Prefabs/Classes/CubePrefab.h"
#include "Utils/MathUtils.h"

#include "Prefabs/Game/Tiles/BreakableBlock.h"
#include "Prefabs/Game/Tiles/UnbreakableBlock.h"

const float TileGridMap::m_TileSize = 1.f; // hardcoded for now, idk if this will ever change
const std::wstring TileGridMap::m_TagName = L"TileMap"; // hardcoded for now, idk if this will ever change

TileGridMap::TileGridMap(int width, int height)
	: m_MapSize{ width, height }
{
}

bool TileGridMap::IsTileOccupied(int x, int y) const
{
	return IsTileOccupied(XMINT2{x, y});
}
bool TileGridMap::IsTileOccupied(const XMINT2& coordinate) const
{
	for (GridCoordinateComponent* pGridEntity : m_pMapEntities)
	{
		if (pGridEntity->GetCoordinate() == coordinate)
		{
			return true;
		}
	}
	return false;
}

bool TileGridMap::IsTileBlocked(int x, int y) const
{
	return IsTileBlocked(XMINT2{ x, y });
}
bool TileGridMap::IsTileBlocked(const XMINT2& coordinate) const
{
	for (GridCoordinateComponent* pGridEntity : m_pMapEntities)
	{
		if (pGridEntity->GetCoordinate() == coordinate && pGridEntity->GetIsBlocking())
		{
			return true;
		}
	}
	return false;
}

void TileGridMap::AddTileEntity(GridCoordinateComponent* pEntityToAdd)
{
	auto entityPos = std::find(m_pMapEntities.begin(), m_pMapEntities.end(), pEntityToAdd);
	if (entityPos == m_pMapEntities.end())
	{
		m_pMapEntities.push_back(pEntityToAdd);
	}
}
void TileGridMap::RemoveTileEntity(GridCoordinateComponent* pEntityToRemove)
{
	auto entityPos = std::find(m_pMapEntities.begin(), m_pMapEntities.end(), pEntityToRemove);
	if (entityPos != m_pMapEntities.end())
	{
		m_pMapEntities.erase(entityPos);
	}
}

XMFLOAT3 TileGridMap::GetTilePositionAt(const XMINT2& coordinate)
{
	return GetTilePositionAt(coordinate.x, coordinate.y);
}
XMFLOAT3 TileGridMap::GetTilePositionAt(int x, int y)
{
	XMFLOAT3 pos = GetBottomLeftSpawnLocation();
	pos.x += x * m_TileSize;
	pos.z += y * m_TileSize;
	return pos;
}

XMINT2 TileGridMap::GetMapSize() const
{
	return m_MapSize;
}

void TileGridMap::Initialize(const SceneContext& /*sceneContext*/)
{
	// Give out GO the 'TileMap' tag, important to be able to find this GO later/in other code
	GetGameObject()->SetTag(m_TagName);

	// Reserve a decent amount of space for tile entities, 2.5x amount of tiles should do
	const int mapTiles = m_MapSize.x * m_MapSize.y;
	m_pMapEntities.reserve(mapTiles * 2 + mapTiles / 2);

	SpawnBackgroundTiles();
	SpawnEdgeUnbreakables();
	SpawnPlayfieldUnbreakables();

	// spawn breakables on the field
	// do it everywhere there's no unbreakable
	SpawnBreakables();
	// then clear out the corners
	ClearCornerBlocks();
	// then clear out some blocks in random positions
	ClearRandomAmountOfBreakables(14); // static amount for now
}

#pragma region Spawning
void TileGridMap::SpawnBackgroundTiles()
{
	const XMFLOAT3 tileDimensions{ m_TileSize, m_TileSize, m_TileSize };
	XMFLOAT3 spawnPos = GetBottomLeftSpawnLocation();
	spawnPos.y -= m_TileSize; // Make it on the ground

	XMFLOAT4 startColor = m_LightBackGroundTileColor;
	float startZ = spawnPos.z;
	for (int row = 0; row < m_MapSize.x; row++)
	{
		XMFLOAT4 colorToUse = startColor;
		for (int col = 0; col < m_MapSize.y; col++)
		{
			// spawn cube at place with color
			GameObject* tile = new CubePrefab(tileDimensions, colorToUse);
			tile->GetTransform()->Translate(spawnPos);
			GetScene()->AddChild(tile);

			// move distance +y with tileSize
			spawnPos.z += m_TileSize;

			// change color
			SwapColor(colorToUse);
		}
		spawnPos.z = startZ;
		spawnPos.x += m_TileSize;

		SwapColor(startColor);
	}
}

void TileGridMap::SpawnEdgeUnbreakables()
{
	const XMFLOAT3 tileDimensions{ m_TileSize, m_TileSize, m_TileSize };
	XMFLOAT3 spawnPos = GetBottomLeftSpawnLocation();

	float startZ = spawnPos.z;
	for (int row = 0; row < m_MapSize.x; row++)
	{
		for (int col = 0; col < m_MapSize.y; col++)
		{
			if (row == 0 || row == m_MapSize.x - 1 || col == 0 || col == m_MapSize.y - 1) // if on any edge
			{
				GameObject* unbreakable = new UnbreakableBlock(XMINT2{ row, col });
				unbreakable->GetTransform()->Translate(GetTilePositionAt(row, col));
				GetScene()->AddChild(unbreakable);
			}

			spawnPos.z += m_TileSize;
		}
		spawnPos.z = startZ;
		spawnPos.x += m_TileSize;
	}
}

void TileGridMap::SpawnPlayfieldUnbreakables()
{
	const XMFLOAT3 tileDimensions{ m_TileSize, m_TileSize, m_TileSize };
	XMFLOAT3 spawnPos = GetBottomLeftSpawnLocation();
	spawnPos.x += m_TileSize;
	spawnPos.z += m_TileSize;

	float startZ = spawnPos.z;
	for (int row = 1; row < m_MapSize.x - 1; row++)
	{
		for (int col = 1; col < m_MapSize.y - 1; col++)
		{
			if (row % 2 == 0 && col % 2 == 0)
			{
				GameObject* unbreakable = new UnbreakableBlock(XMINT2{ row, col });
				unbreakable->GetTransform()->Translate(GetTilePositionAt(row, col));
				GetScene()->AddChild(unbreakable);
			}

			spawnPos.z += m_TileSize;
		}
		spawnPos.z = startZ;
		spawnPos.x += m_TileSize;
	}
}

void TileGridMap::SpawnBreakables()
{
	const XMFLOAT3 tileDimensions{ m_TileSize * 0.75f, m_TileSize * 0.75f, m_TileSize * 0.75f };
	XMFLOAT3 spawnPos = GetBottomLeftSpawnLocation();

	float startZ = spawnPos.z;
	for (int row = 0; row < m_MapSize.x; row++)
	{
		for (int col = 0; col < m_MapSize.y; col++)
		{
			if (!IsTileOccupied(row, col))
			{
				GameObject* breakable = new BreakableBlock(XMINT2{ row, col });
				breakable->GetTransform()->Translate(GetTilePositionAt(row, col));
				GetScene()->AddChild(breakable);
			}
			spawnPos.z += m_TileSize;
		}
		spawnPos.z = startZ;
		spawnPos.x += m_TileSize;
	}
}

void TileGridMap::ClearCornerBlocks()
{
	// Get coordinates of blocks which have to go
	std::vector<XMINT2> coordinatesToRemoveBlocksAt{}; 
	coordinatesToRemoveBlocksAt.reserve(12); // 4 corners, 3 blocks per corner = 12 spots needed

	{
		// bottom left
		coordinatesToRemoveBlocksAt.push_back(XMINT2{ 1, 1 });
		coordinatesToRemoveBlocksAt.push_back(XMINT2{ 1, 2 });
		coordinatesToRemoveBlocksAt.push_back(XMINT2{ 2, 1 });

		// bottom right
		coordinatesToRemoveBlocksAt.push_back(XMINT2{ m_MapSize.x - 2, 1 });
		coordinatesToRemoveBlocksAt.push_back(XMINT2{ m_MapSize.x - 2, 2 });
		coordinatesToRemoveBlocksAt.push_back(XMINT2{ m_MapSize.x - 3, 1 });

		// top left
		coordinatesToRemoveBlocksAt.push_back(XMINT2{ 1, m_MapSize.y - 2 });
		coordinatesToRemoveBlocksAt.push_back(XMINT2{ 1, m_MapSize.y - 3 });
		coordinatesToRemoveBlocksAt.push_back(XMINT2{ 2, m_MapSize.y - 2 });

		// top right
		coordinatesToRemoveBlocksAt.push_back(XMINT2{ m_MapSize.x - 2, m_MapSize.y - 2 });
		coordinatesToRemoveBlocksAt.push_back(XMINT2{ m_MapSize.x - 2, m_MapSize.y - 3 });
		coordinatesToRemoveBlocksAt.push_back(XMINT2{ m_MapSize.x - 3, m_MapSize.y - 2 });
	}

	// Delete those blocks
	for (const XMINT2& coordinate : coordinatesToRemoveBlocksAt)
	{
		DeleteEntitiesAt(coordinate);
	}
}

void TileGridMap::ClearRandomAmountOfBreakables(int amountToClear)
{
	int consecutiveFailedAttempts = 0;
	for (int amountCleared = 0; amountCleared < amountToClear;)
	{
		int index{ RandomInRange(0, static_cast<int>(m_pMapEntities.size()) - 1)};
		GridCoordinateComponent* pEntity = m_pMapEntities[index];
		if (dynamic_cast<BreakableBlock*>(pEntity->GetGameObject()) != nullptr)
		{
			GetScene()->RemoveChild(pEntity->GetGameObject(), true);

			amountCleared++;
			consecutiveFailedAttempts = 0;
		}
		else
		{
			consecutiveFailedAttempts++;
		}

		if (consecutiveFailedAttempts >= amountToClear)
		{
			return; // just to make sure we never get stuck in here
		}
	}
}
#pragma endregion Spawning

#pragma region Helpers
void TileGridMap::SwapColor(XMFLOAT4& colorToSwap) const
{
	if (colorToSwap == m_LightBackGroundTileColor)
	{
		colorToSwap = m_DarkBackGroundTileColor;
	}
	else
	{
		colorToSwap = m_LightBackGroundTileColor;
	}
}

XMFLOAT3 TileGridMap::GetBottomLeftSpawnLocation() const
{
	TransformComponent* pTransform = GetTransform();
	XMFLOAT3 spawnPos = pTransform->GetPosition();

	int widthTileDistancesToMove = m_MapSize.x / 2;
	int heightTileDistancesToMove = m_MapSize.y / 2;
	spawnPos.x -= m_TileSize * widthTileDistancesToMove;
	spawnPos.z -= m_TileSize * heightTileDistancesToMove;
	if (m_MapSize.x % 2 == 0)
	{
		spawnPos.x += m_TileSize / 2;
	}
	if (m_MapSize.y % 2 == 0)
	{
		spawnPos.z += m_TileSize / 2;
	}

	return spawnPos;
}

void TileGridMap::DeleteEntitiesAt(const XMINT2& coordinate)
{
	std::vector<GridCoordinateComponent*> pEnitiesAtCoordinate{};
	for (GridCoordinateComponent* pEntity : m_pMapEntities)
	{
		if (pEntity->GetCoordinate() == coordinate)
		{
			pEnitiesAtCoordinate.push_back(pEntity);
		}
	}

	for (size_t i = 0; i < pEnitiesAtCoordinate.size(); i++)
	{
		GetScene()->RemoveChild(pEnitiesAtCoordinate[i]->GetGameObject(), true);
	}
}
#pragma endregion Helpers

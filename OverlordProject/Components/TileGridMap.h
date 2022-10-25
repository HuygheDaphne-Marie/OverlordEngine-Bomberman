#pragma once
#include "..\OverlordEngine\Components\BaseComponent.h"
#include "Components/GridCoordinateComponent.h"
#include "Utils/MathUtils.h"
/*
* component which handles 'being' the map
* 
* X spawns tiles where they should be when initialised
* X can be queried for movement collision
* X everything which is on the grid should be contained within this
* 
* - can be queried about location of a gameobject (asking for a grid pos based on it's transform, might be needed for bombs)
*		could maybe also only set the new grid pos when moving halfway trough the move (with a duration or something)
*/

class TileGridMap : public BaseComponent
{
public:
	static const float m_TileSize;
	static const std::wstring m_TagName;

	TileGridMap(int width, int height);
	~TileGridMap() override = default;

	TileGridMap(const TileGridMap & other) = delete;
	TileGridMap(TileGridMap && other) noexcept = delete;
	TileGridMap& operator=(const TileGridMap & other) = delete;
	TileGridMap& operator=(TileGridMap && other) noexcept = delete;

	bool IsTileOccupied(int x, int y) const;
	bool IsTileOccupied(const XMINT2& coordinate) const;

	bool IsTileBlocked(int x, int y) const;
	bool IsTileBlocked(const XMINT2& coordinate) const;

	void AddTileEntity(GridCoordinateComponent* pEntityToAdd);
	void RemoveTileEntity(GridCoordinateComponent* pEntityToRemove);

	template<class T>
	T* GetTypeAtCoordinate(const XMINT2& coordinate) const
	{
		static_assert(std::is_same_v<T, GameObject> || std::is_base_of_v<GameObject, T>, "GetTypeAtCoordinate expects a GameObject");

		const type_info& ti = typeid(T);
		for (GridCoordinateComponent* pEnitiy : m_pMapEntities)
		{
			if (pEnitiy->GetCoordinate() == coordinate)
				if (pEnitiy->GetGameObject() && typeid(*pEnitiy->GetGameObject()) == ti)
					return static_cast<T*>(pEnitiy->GetGameObject());
		}
		return nullptr;
	}

	XMFLOAT3 GetTilePositionAt(const XMINT2& coordinate);
	XMFLOAT3 GetTilePositionAt(int x, int y);

	XMINT2 GetMapSize() const;

protected:
	void Initialize(const SceneContext& sceneContext) override;

private:
	const XMINT2 m_MapSize{};
	
	// List of everything with a GridCoordinate
	std::vector<GridCoordinateComponent*> m_pMapEntities{}; // Can be made a set?

	const XMFLOAT4 m_LightBackGroundTileColor{ Colors::LightGreen };
	const XMFLOAT4 m_DarkBackGroundTileColor{ Colors::DarkGreen };

	// Spawning
	void SpawnBackgroundTiles();
	void SpawnEdgeUnbreakables();
	void SpawnPlayfieldUnbreakables();
	void SpawnBreakables();
	void ClearCornerBlocks();
	void ClearRandomAmountOfBreakables(int amountToClear);

	// Helpers
	void SwapColor(XMFLOAT4& colorToSwap) const;
	XMFLOAT3 GetBottomLeftSpawnLocation() const;
	void DeleteEntitiesAt(const XMINT2& coordinate);
};


#pragma once
#include "..\OverlordEngine\Scenegraph\GameObject.h"
#include "Components/GridCoordinateComponent.h"

// Represents anything which should be kept track of on the TileMap
class TileEntity : public GameObject
{
	// At bare minimum needs a position on the grid (that's valid?)
		// so gridtile coord comp needed

public:
	TileEntity(int x, int y);
	~TileEntity() override = default;
	TileEntity(const TileEntity & other) = delete;
	TileEntity(TileEntity && other) noexcept = delete;
	TileEntity& operator=(const TileEntity & other) = delete;
	TileEntity& operator=(TileEntity && other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
};


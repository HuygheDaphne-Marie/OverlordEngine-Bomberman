#pragma once
#include "..\OverlordEngine\Components\BaseComponent.h"

// Really regretting making this a component instead of a part of the TileEntity GO

class GridCoordinateComponent : public BaseComponent
{
public:
	GridCoordinateComponent(const XMINT2& coordinate, bool isBlocking = false);
	GridCoordinateComponent(int x, int y, bool isBlocking = false);
	~GridCoordinateComponent() override = default;

	GridCoordinateComponent(const GridCoordinateComponent& other) = delete;
	GridCoordinateComponent(GridCoordinateComponent&& other) noexcept = delete;
	GridCoordinateComponent& operator=(const GridCoordinateComponent& other) = delete;
	GridCoordinateComponent& operator=(GridCoordinateComponent&& other) noexcept = delete;

	const XMINT2& GetCoordinate() const;
	void SetCoordinate(const XMINT2& coordinate);
	void SetCoordinate(int x, int y);

	bool GetIsBlocking() const;
	void SetIsBlocking(bool isBlocking);

protected:
	void Initialize(const SceneContext& /*sceneContext*/) override;
	void OnSceneAttach(GameScene* pScene) override;
	void OnSceneDetach(GameScene* pScene) override;

private:
	XMINT2 m_Coordinate{};
	bool m_IsBlocking{};
};


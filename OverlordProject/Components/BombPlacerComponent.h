#pragma once
#include "..\OverlordEngine\Components\BaseComponent.h"
#include "Components/GridCoordinateComponent.h"
#include "Components/TileGridMap.h"

class Bomb;

class BombPlacerComponent : public BaseComponent
{
public:
	BombPlacerComponent(int bombLimit = 1, int explosionRadius = 1);
	virtual ~BombPlacerComponent() = default;
	BombPlacerComponent(const BombPlacerComponent & other) = delete;
	BombPlacerComponent(BombPlacerComponent && other) noexcept = delete;
	BombPlacerComponent& operator=(const BombPlacerComponent & other) = delete;
	BombPlacerComponent& operator=(BombPlacerComponent && other) noexcept = delete;

	void PlaceBomb();
	void OnBombExplode(Bomb* pBomb);

	void IncreaseBombLimit();
	void IncreaseExplosionRadius();

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void OnSceneDetach(GameScene* pScene) override;

private:
	GridCoordinateComponent* m_pMyCoordinate{};
	TileGridMap* m_pMap{};
	FMOD::Sound* m_pPlaceSound{};

	int m_BombLimit{};
	std::vector<Bomb*> m_pCurrentBombs{};
	int m_ExplosionRadius{};
};


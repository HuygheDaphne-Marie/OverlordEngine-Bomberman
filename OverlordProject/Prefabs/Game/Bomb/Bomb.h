#pragma once
#include "Prefabs/Game/Tiles/TileEntity.h"
#include "Components/TileGridMap.h"
class BombPlacerComponent;

class Bomb : public TileEntity
{
public:
	Bomb(BombPlacerComponent* pPlacer, const XMINT2& coordinate, int explosionRadius); // timer static across all bombs
	~Bomb() override = default;
	Bomb(const Bomb & other) = delete;
	Bomb(Bomb && other) noexcept = delete;
	Bomb& operator=(const Bomb & other) = delete;
	Bomb& operator=(Bomb && other) noexcept = delete;

	void PlayerDestroyed(BombPlacerComponent* pPlacer);

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	GridCoordinateComponent* m_pPosition{};
	TileGridMap* m_pMap{};
	BombPlacerComponent* m_pPlacer{};
	FMOD::Sound* m_pExplosionSound{};

	static float m_ExplosionCountdownDuration;
	float m_CountdownTimer{};
	const int m_ExplosionRadius{};

	void Explode();
	void ExplodeInDirection(const XMINT2& direction, int distance);
	void ExplodeAt(const XMINT2& location);
};


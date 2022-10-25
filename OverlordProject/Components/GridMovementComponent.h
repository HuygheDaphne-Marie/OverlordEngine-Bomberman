#pragma once
#include "..\OverlordEngine\Components\BaseComponent.h"

class GridCoordinateComponent;
class TileGridMap;

/*
* Component which will be used by players' input component to command it to move places if it can
* 
* - should have simple interface (moveNorth/moveEast/moveSouth/moveWest)
*		if already moving, do nothing
*		if not able to move that way, do nothing
*		if able to move, make characterController component move in that direction
*			towards a point but for a DURATION (should have a momentduration variable here)
*			once half of the movement duration has passed, set gridCoord to new coord
*				might need to spawn a temporary GO to block the coordinate we're heading towards & delete it when we arrive/take the position
*/

enum class MoveDirection
{
	North,
	East,
	South,
	West
};

class GridMovementComponent : public BaseComponent
{
public:
	GridMovementComponent(float movementDuration);
	~GridMovementComponent() override = default;

	GridMovementComponent(const GridMovementComponent & other) = delete;
	GridMovementComponent(GridMovementComponent && other) noexcept = delete;
	GridMovementComponent& operator=(const GridMovementComponent & other) = delete;
	GridMovementComponent& operator=(GridMovementComponent && other) noexcept = delete;

	bool IsMoving() const;

	bool MoveNorth();
	bool MoveEast();
	bool MoveSouth();
	bool MoveWest();
	bool Move(const MoveDirection& direction);

	void IncreaseMovementSpeed();

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	TileGridMap* m_pMap{};
	GridCoordinateComponent* m_pMyCoordinate{};
	XMINT2 m_Origin{};
	XMINT2 m_Destination{};
	GridCoordinateComponent* m_pMyMovementBlocker{};

	FMOD::Sound* m_pWalkSound{};

	float m_MovementDuration{1.0f};
	float m_MovementTimer{};

	static const float m_MovementSpeedPickupPercentageModifier;

	bool Move(const XMINT2& delta);
};


#pragma once
#include "TileEntity.h"

class MovementBlocker : public TileEntity
{
public:
	MovementBlocker(const XMINT2& coordinate);
	~MovementBlocker() override = default;
	MovementBlocker(const MovementBlocker & other) = delete;
	MovementBlocker(MovementBlocker && other) noexcept = delete;
	MovementBlocker& operator=(const MovementBlocker & other) = delete;
	MovementBlocker& operator=(MovementBlocker && other) noexcept = delete;

protected:
	void Initialize(const SceneContext& /*sceneContext*/) override;
};


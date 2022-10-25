#pragma once
#include "Scenegraph/GameScene.h"

class ModelTestScene : public GameScene
{
public:
	ModelTestScene();
	~ModelTestScene() override = default;

protected:
	// Inherited via GameScene
	virtual void Initialize() override;

private:
	GameObject* m_pChair = nullptr;
};


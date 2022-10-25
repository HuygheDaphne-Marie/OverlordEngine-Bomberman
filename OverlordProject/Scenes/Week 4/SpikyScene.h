#pragma once
#include "Scenegraph/GameScene.h"

class SpikyMaterial;

class SpikyScene : public GameScene
{
public:
	SpikyScene();
	~SpikyScene() override = default;


protected:
	virtual void Initialize() override;
	virtual void OnGUI() override;
	virtual void Update() override;

private:
	GameObject* m_pBall{};
	SpikyMaterial* m_pMaterial{};
};


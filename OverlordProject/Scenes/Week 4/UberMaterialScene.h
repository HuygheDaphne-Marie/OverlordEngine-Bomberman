#pragma once
#include "Scenegraph/GameScene.h"

class UberMaterial;

class UberMaterialScene : public GameScene
{
public:
	UberMaterialScene();
	~UberMaterialScene() override = default;

protected:
	virtual void Initialize() override;
	virtual void OnGUI() override;

private:
	GameObject* m_MatSphere{};
	UberMaterial* m_pSphereMat{};
};


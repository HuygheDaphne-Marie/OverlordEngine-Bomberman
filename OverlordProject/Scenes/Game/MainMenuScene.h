#pragma once
#include "..\OverlordEngine\Scenegraph\GameScene.h"
#include "Prefabs/Game/Managers/UIInputManager.h"

class MainMenuScene : public GameScene
{
public:
	MainMenuScene() :GameScene(L"MainMenuScene") {}
	~MainMenuScene() override = default;
	MainMenuScene(const MainMenuScene & other) = delete;
	MainMenuScene(MainMenuScene && other) noexcept = delete;
	MainMenuScene& operator=(const MainMenuScene & other) = delete;
	MainMenuScene& operator=(MainMenuScene && other) noexcept = delete;

protected:
	void Initialize() override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

private:
	SpriteFont* m_pMenuFont{};
	const float m_MenuPosX{ 150.f };

	UIInputManager* m_pUIInputManager{};
};


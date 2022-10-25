#pragma once
#include "..\OverlordEngine\Scenegraph\GameObject.h"

class Player;

class GameEndScreen : public GameObject
{
public:
	GameEndScreen(Player* pWinner);
	~GameEndScreen() override = default;
	GameEndScreen(const GameEndScreen & other) = delete;
	GameEndScreen(GameEndScreen && other) noexcept = delete;
	GameEndScreen& operator=(const GameEndScreen & other) = delete;
	GameEndScreen& operator=(GameEndScreen && other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	Player* m_pWinner{};
	std::string m_EndText{};
	SpriteFont* m_pFont{};
	float m_MenuX{};
};


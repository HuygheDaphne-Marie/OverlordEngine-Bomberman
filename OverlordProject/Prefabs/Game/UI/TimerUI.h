#pragma once
#include "..\OverlordEngine\Scenegraph\GameObject.h"

class GameManager;

class TimerUI : public GameObject
{
public:
	TimerUI(GameManager* pGameManager);
	~TimerUI() override = default;
	TimerUI(const TimerUI& other) = delete;
	TimerUI(TimerUI&& other) noexcept = delete;
	TimerUI& operator=(const TimerUI& other) = delete;
	TimerUI& operator=(TimerUI&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	GameManager* m_pGameManager{};
	SpriteFont* m_pFont{};
	XMFLOAT2 m_Pos{};
};


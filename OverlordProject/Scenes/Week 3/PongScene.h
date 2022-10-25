#pragma once
#include "Scenegraph/GameScene.h"
class PongScene final : public GameScene
{
public:
	PongScene();
	~PongScene() override = default;

	PongScene(const PongScene & other) = delete;
	PongScene(PongScene && other) noexcept = delete;
	PongScene& operator=(const PongScene & other) = delete;
	PongScene& operator=(PongScene && other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;

private:

	enum class InputIds
	{
		ArrowUp,
		ArrowDown,
		KeyboardUp,
		KeyboardDown
	};

	bool m_ShouldSceneReset = false;

	const float m_HalfFieldSize{ 30.f };
	const XMFLOAT3 m_HalfPaddle{0.5f, 0.5f, 2.f};
	const float m_BallSpeed{ 5.f };

	GameObject* m_pLeftPaddle = nullptr;
	GameObject* m_pRightPaddle = nullptr;
	GameObject* m_pBall = nullptr;

	GameObject* m_pLeftTrigger = nullptr;
	GameObject* m_pRightTrigger = nullptr;

	//GameObject* CreatePaddle(PxMaterial* material);
	// 	typedef std::function<void (GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action)> PhysicsCallback;
	void OnTrigger(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action);

	void ResetScene();
};


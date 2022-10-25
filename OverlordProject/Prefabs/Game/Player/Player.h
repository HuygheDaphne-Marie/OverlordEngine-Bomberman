#pragma once
#include "Prefabs/Game/Tiles/TileEntity.h"
#include "Components/CharacterInputComponent.h"
#include "Components/GridMovementComponent.h"
#include "Components/BombPlacerComponent.h"

// The player, will need to be able to process input & pass it to it's

class PlayerUI;

class Player : public TileEntity
{
public:
	static const std::wstring m_TagName;

	Player(const XMINT2& coordinate, const CharacterInputComponent::InputDesc& inputActions);
	~Player() override = default;
	Player(const Player & other) = delete;
	Player(Player && other) noexcept = delete;
	Player& operator=(const Player & other) = delete;
	Player& operator=(Player && other) noexcept = delete;

	void Kill();
	void SetPlayerUI(PlayerUI* pUI);
	void SetPlayerNumber(int playerNumber);
	int GetPlayerNumber() const;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;
	void OnSceneDetach(GameScene* pScene) override;

private:
	enum AnimationIds
	{
		idle, // for some reason, even though it's the **exact** same animation, this refuses to play
		run,
		idle2
	};
	
	const CharacterInputComponent::InputDesc m_InputActions; // kept here for use in initialise 

	ModelAnimator* m_pAnimator{};
	AnimationIds m_CurrentAnimationClipId{ AnimationIds::idle2 };
	float m_CurrentAnimationSpeed{ 2.f };

	GridMovementComponent* m_pMover{};

	PlayerUI* m_pMyUI{};
	int m_PlayerNumber{ -1 };
};

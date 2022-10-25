#pragma once
#include "..\OverlordEngine\Components\BaseComponent.h"
#include "Components/GridMovementComponent.h"
#include "Components/BombPlacerComponent.h"

class CharacterInputComponent : public BaseComponent
{
public:
	struct InputDesc
	{
		InputDesc() :
			actionId_MoveLeft(-1),
			actionId_MoveRight(-1),
			actionId_MoveUp(-1),
			actionId_MoveDown(-1),
			actionId_PlaceBomb(-1),

			keyboard_MoveLeft(-1),
			keyboard_MoveRight(-1),
			keyboard_MoveUp(-1),
			keyboard_MoveDown(-1),
			keyboard_PlaceBomb(-1),
			
			playerIndex(GamepadIndex::playerOne),
			gamepad_MoveLeft(0),
			gamepad_MoveRight(0),
			gamepad_MoveUp(0),
			gamepad_MoveDown(0),
			gamepad_PlaceBomb(0)
			{}

		InputDesc(int idMoveLeft, int idMoveRight, int idMoveUp, int idMoveDown, int idPlaceBomb, 
			int keyboardMoveLeft, int keyboardMoveRight, int keyboardMoveUp, int keyboardMoveDown, int keyboardPlaceBomb) :
			actionId_MoveLeft(idMoveLeft),
			actionId_MoveRight(idMoveRight),
			actionId_MoveUp(idMoveUp),
			actionId_MoveDown(idMoveDown),
			actionId_PlaceBomb(idPlaceBomb),

			keyboard_MoveLeft(keyboardMoveLeft),
			keyboard_MoveRight(keyboardMoveRight),
			keyboard_MoveUp(keyboardMoveUp),
			keyboard_MoveDown(keyboardMoveDown),
			keyboard_PlaceBomb(keyboardPlaceBomb),

			playerIndex(GamepadIndex::playerOne),
			gamepad_MoveLeft(0),
			gamepad_MoveRight(0),
			gamepad_MoveUp(0),
			gamepad_MoveDown(0),
			gamepad_PlaceBomb(0)
		{}

		InputDesc(int idMoveLeft, int idMoveRight, int idMoveUp, int idMoveDown, int idPlaceBomb, GamepadIndex playerIndex,
			WORD gamepadMoveLeft, WORD gamepadMoveRight, WORD gamepadMoveUp, WORD gamepadMoveDown, WORD gamepadPlaceBomb) :
			actionId_MoveLeft(idMoveLeft),
			actionId_MoveRight(idMoveRight),
			actionId_MoveUp(idMoveUp),
			actionId_MoveDown(idMoveDown),
			actionId_PlaceBomb(idPlaceBomb),

			keyboard_MoveLeft(-1),
			keyboard_MoveRight(-1),
			keyboard_MoveUp(-1),
			keyboard_MoveDown(-1),
			keyboard_PlaceBomb(-1),

			playerIndex(playerIndex),
			gamepad_MoveLeft(gamepadMoveLeft),
			gamepad_MoveRight(gamepadMoveRight),
			gamepad_MoveUp(gamepadMoveUp),
			gamepad_MoveDown(gamepadMoveDown),
			gamepad_PlaceBomb(gamepadPlaceBomb)
		{}

		// ids, always needed
		int actionId_MoveLeft{ -1 };
		int actionId_MoveRight{ -1 };
		int actionId_MoveUp{ -1 };
		int actionId_MoveDown{ -1 };
		int actionId_PlaceBomb{ -1 };

		// binds, only needs one (Keyboard/Gamepad)
		int keyboard_MoveLeft = -1;
		int keyboard_MoveRight = -1;
		int keyboard_MoveUp = -1;
		int keyboard_MoveDown = -1;
		int keyboard_PlaceBomb = -1;

		GamepadIndex playerIndex = GamepadIndex::playerOne;
		WORD gamepad_MoveLeft = 0;
		WORD gamepad_MoveRight = 0;
		WORD gamepad_MoveUp = 0;
		WORD gamepad_MoveDown = 0;
		WORD gamepad_PlaceBomb = 0;
	};

	CharacterInputComponent(const InputDesc& input, GridMovementComponent* pMovement, BombPlacerComponent* pBombPlacer);
	~CharacterInputComponent() override = default;
	CharacterInputComponent(const CharacterInputComponent & other) = delete;
	CharacterInputComponent(CharacterInputComponent && other) noexcept = delete;
	CharacterInputComponent& operator=(const CharacterInputComponent & other) = delete;
	CharacterInputComponent& operator=(CharacterInputComponent && other) noexcept = delete;

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	InputDesc m_InputDesc{};
	GridMovementComponent* m_pMovement{};
	BombPlacerComponent* m_pBombPlacer{};
};


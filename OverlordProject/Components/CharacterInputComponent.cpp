#include "stdafx.h"
#include "CharacterInputComponent.h"

CharacterInputComponent::CharacterInputComponent(const InputDesc& input, GridMovementComponent* pMovement, BombPlacerComponent* pBombPlacer)
	: m_InputDesc{input}
	, m_pMovement{pMovement}
	, m_pBombPlacer{pBombPlacer}
{
}

void CharacterInputComponent::Initialize(const SceneContext& sceneContext)
{
	// Movement
	auto inputAction = InputAction(
		m_InputDesc.actionId_MoveLeft, 
		InputState::down, 
		m_InputDesc.keyboard_MoveLeft, 
		-1, 
		m_InputDesc.gamepad_MoveLeft, 
		m_InputDesc.playerIndex
	);
	sceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(
		m_InputDesc.actionId_MoveRight, 
		InputState::down, 
		m_InputDesc.keyboard_MoveRight, 
		-1, 
		m_InputDesc.gamepad_MoveRight, 
		m_InputDesc.playerIndex
	);
	sceneContext.pInput->AddInputAction(inputAction);

	inputAction = InputAction(
		m_InputDesc.actionId_MoveUp, 
		InputState::down, 
		m_InputDesc.keyboard_MoveUp, 
		-1, 
		m_InputDesc.gamepad_MoveUp, 
		m_InputDesc.playerIndex
	);
	sceneContext.pInput->AddInputAction(inputAction);
	
	inputAction = InputAction(
		m_InputDesc.actionId_MoveDown, 
		InputState::down, 
		m_InputDesc.keyboard_MoveDown,
		-1,
		m_InputDesc.gamepad_MoveDown,
		m_InputDesc.playerIndex
	);
	sceneContext.pInput->AddInputAction(inputAction);

	// Bomb Place
	inputAction = InputAction(
		m_InputDesc.actionId_PlaceBomb, 
		InputState::pressed, 
		m_InputDesc.keyboard_PlaceBomb,
		-1,
		m_InputDesc.gamepad_PlaceBomb,
		m_InputDesc.playerIndex
	);
	sceneContext.pInput->AddInputAction(inputAction);
}

void CharacterInputComponent::Update(const SceneContext& sceneContext)
{
	// Handle Movement Input
	if (sceneContext.pInput->IsActionTriggered(m_InputDesc.actionId_MoveLeft))
	{
		if (m_pMovement->MoveWest())
		{
			GetTransform()->Rotate(0, 90.f, 0);
		}
	}
	else if (sceneContext.pInput->IsActionTriggered(m_InputDesc.actionId_MoveRight))
	{
		if (m_pMovement->MoveEast())
		{
			GetTransform()->Rotate(0, -90.f, 0);
		}
	}
	else if (sceneContext.pInput->IsActionTriggered(m_InputDesc.actionId_MoveUp))
	{
		if (m_pMovement->MoveNorth())
		{
			GetTransform()->Rotate(0, 180.f, 0);
		}
	}
	else if (sceneContext.pInput->IsActionTriggered(m_InputDesc.actionId_MoveDown))
	{
		if (m_pMovement->MoveSouth())
		{
			GetTransform()->Rotate(0, 0, 0);
		}
	}
	else if (sceneContext.pInput->IsActionTriggered(m_InputDesc.actionId_PlaceBomb))
	{
		m_pBombPlacer->PlaceBomb();
	}
}

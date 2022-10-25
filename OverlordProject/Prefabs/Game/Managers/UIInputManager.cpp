#include "stdafx.h"
#include "UIInputManager.h"
#include "Prefabs/Game/UI/Button.h"

const std::wstring UIInputManager::m_TagName{L"UIInputManager"};

UIInputManager::UIInputManager(Button* pFirstSelected)
	: GameObject{}
	, m_pFirstSelected{pFirstSelected}
{
	RegisterButton(pFirstSelected);
	UpdateCurrentSelected(pFirstSelected);
}

void UIInputManager::BindInput()
{
	InputManager* pInput{ GetScene()->GetSceneContext().pInput };

	// Select
	{
		InputAction selectAction{ UIInputIds::select, InputState::pressed, VK_RETURN, VK_LBUTTON, XINPUT_GAMEPAD_A };
		pInput->AddInputAction(selectAction);
		//selectAction.playerIndex = GamepadIndex::playerTwo;
		//pInput->AddInputAction(selectAction);
		//selectAction.playerIndex = GamepadIndex::playerThree;
		//pInput->AddInputAction(selectAction);
		//selectAction.playerIndex = GamepadIndex::playerFour;
		//pInput->AddInputAction(selectAction);
	}

	// Up
	{
		InputAction upAction{ UIInputIds::up, InputState::pressed, VK_UP, -1, XINPUT_GAMEPAD_DPAD_UP };
		pInput->AddInputAction(upAction);
		//upAction.playerIndex = GamepadIndex::playerTwo;
		//pInput->AddInputAction(upAction);
		//upAction.playerIndex = GamepadIndex::playerThree;
		//pInput->AddInputAction(upAction);
		//upAction.playerIndex = GamepadIndex::playerFour;
		//pInput->AddInputAction(upAction);
	}

	// Down
	{
		InputAction downAction{ UIInputIds::down, InputState::pressed, VK_DOWN, -1, XINPUT_GAMEPAD_DPAD_DOWN };
		pInput->AddInputAction(downAction);
		//downAction.playerIndex = GamepadIndex::playerTwo;
		//pInput->AddInputAction(downAction);
		//downAction.playerIndex = GamepadIndex::playerThree;
		//pInput->AddInputAction(downAction);
		//downAction.playerIndex = GamepadIndex::playerFour;
		//pInput->AddInputAction(downAction);
	}

	// Right
	{
		InputAction rightAction{ UIInputIds::right, InputState::pressed, VK_RIGHT, -1, XINPUT_GAMEPAD_DPAD_RIGHT };
		pInput->AddInputAction(rightAction);
		//rightAction.playerIndex = GamepadIndex::playerTwo;
		//pInput->AddInputAction(rightAction);
		//rightAction.playerIndex = GamepadIndex::playerThree;
		//pInput->AddInputAction(rightAction);
		//rightAction.playerIndex = GamepadIndex::playerFour;
		//pInput->AddInputAction(rightAction);
	}

	// Left
	{
		InputAction leftAction{ UIInputIds::left, InputState::pressed, VK_LEFT, -1, XINPUT_GAMEPAD_DPAD_LEFT };
		pInput->AddInputAction(leftAction);
		//leftAction.playerIndex = GamepadIndex::playerTwo;
		//pInput->AddInputAction(leftAction);
		//leftAction.playerIndex = GamepadIndex::playerThree;
		//pInput->AddInputAction(leftAction);
		//leftAction.playerIndex = GamepadIndex::playerFour;
		//pInput->AddInputAction(leftAction);
	}

	m_IsInputBound = true;
}

void UIInputManager::UnbindInput()
{
	InputManager* pInput{ GetScene()->GetSceneContext().pInput };

	pInput->RemoveInputAction(UIInputIds::select);
	pInput->RemoveInputAction(UIInputIds::up);
	pInput->RemoveInputAction(UIInputIds::down);
	pInput->RemoveInputAction(UIInputIds::right);
	pInput->RemoveInputAction(UIInputIds::left);

	m_IsInputBound = false;
}

void UIInputManager::RegisterButton(Button* pButton)
{
	const auto pButtonItr = std::find(m_pButtons.begin(), m_pButtons.end(), pButton);
	if (pButtonItr == m_pButtons.end()) // not in list
		m_pButtons.push_back(pButton);
}

void UIInputManager::Update(const SceneContext& sceneContext)
{
	if (!m_IsInputBound || m_pCurrentSelected == nullptr)
		return;

	const InputManager* pInput{ sceneContext.pInput };

	// check if we're selecting something
	if (pInput->IsActionTriggered(UIInputIds::select))
	{
		m_pCurrentSelected->OnPress();
		return;
	}

	// check if we're going up/down/right/left
	if (pInput->IsActionTriggered(UIInputIds::up))
	{
		if (m_pCurrentSelected->m_Up != nullptr)
			UpdateCurrentSelected(m_pCurrentSelected->m_Up);
	}
	else if (pInput->IsActionTriggered(UIInputIds::down))
	{
		if (m_pCurrentSelected->m_Down != nullptr)
			UpdateCurrentSelected(m_pCurrentSelected->m_Down);
	}
	else if (pInput->IsActionTriggered(UIInputIds::right))
	{
		if (m_pCurrentSelected->m_Right != nullptr)
			UpdateCurrentSelected(m_pCurrentSelected->m_Right);
	}
	else if (pInput->IsActionTriggered(UIInputIds::left))
	{
		if (m_pCurrentSelected->m_Left != nullptr)
			UpdateCurrentSelected(m_pCurrentSelected->m_Left);
	}

	// check if our mouse is hovering over something, if so, set it as selected
	for (Button* button : m_pButtons)
	{
		POINT mouseposPoint{ pInput->GetMousePosition() };
		bool isHovering = button->IsHoveringOver(XMFLOAT2{ static_cast<float>(mouseposPoint.x), static_cast<float>(mouseposPoint.y) });
		if (isHovering)
		{
			UpdateCurrentSelected(button);
			return;
		}
	}
}

void UIInputManager::UpdateCurrentSelected(Button* pNewCurrent)
{
	if (m_pCurrentSelected != nullptr)
	{
		m_pCurrentSelected->SetSelected(false);
	}
	if (pNewCurrent != nullptr)
	{
		pNewCurrent->SetSelected(true);
		m_pCurrentSelected = pNewCurrent;
	}
}

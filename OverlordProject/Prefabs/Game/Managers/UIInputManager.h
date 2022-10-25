#pragma once
#include "..\OverlordEngine\Scenegraph\GameObject.h"

class Button;

class UIInputManager : public GameObject
{
public:
	static const std::wstring m_TagName;

	UIInputManager(Button* pFirstSelected);
	~UIInputManager() override = default;
	UIInputManager(const UIInputManager& other) = delete;
	UIInputManager(UIInputManager&& other) noexcept = delete;
	UIInputManager& operator=(const UIInputManager& other) = delete;
	UIInputManager& operator=(UIInputManager&& other) noexcept = delete;

	void BindInput();
	void UnbindInput();

	void RegisterButton(Button* pButton);

protected:
	void Initialize(const SceneContext& /*sceneContext*/) {};
	void Update(const SceneContext& sceneContext) override;

private:
	enum UIInputIds
	{
		up = 100,
		down = 101,
		right = 102,
		left = 103,
		select = 104
	};

	bool m_IsInputBound{false};

	std::vector<Button*> m_pButtons{};
	Button const* m_pFirstSelected{};
	Button* m_pCurrentSelected{};

	void UpdateCurrentSelected(Button* pNewCurrent);
};


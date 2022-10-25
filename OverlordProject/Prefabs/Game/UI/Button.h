#pragma once
#include "..\OverlordEngine\Scenegraph\GameObject.h"
class Button : public GameObject
{
public:
	// Which button should be selected on certain input (Like Unity's explicit button nav)
	Button* m_Up{};
	Button* m_Down{};
	Button* m_Right{};
	Button* m_Left{};

	Button(SpriteFont* pFont, const std::string& text, const XMFLOAT2& pos);
	~Button() override = default;
	Button(const Button& other) = delete;
	Button(Button&& other) noexcept = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other) noexcept = delete;

	bool IsHoveringOver(const XMFLOAT2& mousePos) const;
	void SetSelectionZone(const XMFLOAT2& zone);

	void SetSelected(bool isSelected);
	virtual void OnPress();

protected:
	void Initialize(const SceneContext& /*sceneContext*/) override {};
	void Update(const SceneContext& sceneContext) override;

private:
	static const XMFLOAT4 m_SelectedColor;
	static const XMFLOAT4 m_UnselectedColor;
	
	bool m_IsSelected{ false };
	SpriteFont* m_pFont{};
	const std::string m_Text{};
	const XMFLOAT2 m_Pos{};
	
	XMFLOAT2 m_SelectionZone{ 200, 64 };
};


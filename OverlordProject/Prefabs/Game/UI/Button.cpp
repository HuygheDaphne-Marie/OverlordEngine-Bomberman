#include "stdafx.h"
#include "Button.h"

const XMFLOAT4 Button::m_SelectedColor{ Colors::White };
const XMFLOAT4 Button::m_UnselectedColor{ Colors::Gray };

Button::Button(SpriteFont* pFont, const std::string& text, const XMFLOAT2& pos)
	: GameObject()
	, m_pFont{pFont}
	, m_Text{text}
	, m_Pos{pos}
{
}

bool Button::IsHoveringOver(const XMFLOAT2& mousePos) const
{
	const XMFLOAT2 topLeft{ m_Pos.x, m_Pos.y };
	if (mousePos.x < topLeft.x || mousePos.y < topLeft.y)
		return false;

	const XMFLOAT2 bottomRight{ topLeft.x + m_SelectionZone.x, topLeft.y + m_SelectionZone.y };
	if (mousePos.x > bottomRight.x || mousePos.y > bottomRight.y)
		return false;

	return true;
}

void Button::SetSelectionZone(const XMFLOAT2& zone)
{
	m_SelectionZone.x = zone.x;
	m_SelectionZone.y = zone.y;
}

void Button::SetSelected(bool isSelected)
{
	m_IsSelected = isSelected;
}

void Button::OnPress()
{
#pragma warning( push )
#pragma warning( disable : 4996 ) // This is depricated but easiest way I could find to do this
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wide = converter.from_bytes(typeid(this).name());
	Logger::LogDebug(wide);
#pragma warning( pop )
}

void Button::Update(const SceneContext& /*sceneContext*/)
{
	XMFLOAT4 textColor = m_IsSelected ? m_SelectedColor : m_UnselectedColor;
	TextRenderer::Get()->DrawText(m_pFont, StringUtil::utf8_decode(m_Text), m_Pos, textColor);
}

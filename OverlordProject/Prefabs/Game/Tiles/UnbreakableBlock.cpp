#include "stdafx.h"
#include "UnbreakableBlock.h"

const std::wstring UnbreakableBlock::m_BlockTexture{ L"Textures/red_block.png" };

UnbreakableBlock::UnbreakableBlock(const XMINT2& coordinate)
	: Block(coordinate, XMFLOAT3{ 1.0f, 1.0f, 1.0f }, m_BlockTexture)
{
}

#pragma once
#include "Block.h"

class UnbreakableBlock : public Block
{
public:
	UnbreakableBlock(const XMINT2& coordinate);
	~UnbreakableBlock() override = default;

	UnbreakableBlock(const UnbreakableBlock & other) = delete;
	UnbreakableBlock(UnbreakableBlock && other) noexcept = delete;
	UnbreakableBlock& operator=(const UnbreakableBlock & other) = delete;
	UnbreakableBlock& operator=(UnbreakableBlock && other) noexcept = delete;

private:
	const static std::wstring m_BlockTexture;
};


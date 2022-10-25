#pragma once
#include "TileEntity.h"
class Block : public TileEntity
{
public:
	Block(const XMINT2& coordinate, const XMFLOAT3& dimensions, const std::wstring& texture);
	~Block() override = default;

	Block(const Block & other) = delete;
	Block(Block && other) noexcept = delete;
	Block& operator=(const Block & other) = delete;
	Block& operator=(Block && other) noexcept = delete;

protected:
	void Initialize(const SceneContext & sceneContext) override;

private:
	float m_Width{}, m_Height{}, m_Depth{};
	//XMFLOAT4 m_Color{};
	std::wstring m_TexturePath{};
};


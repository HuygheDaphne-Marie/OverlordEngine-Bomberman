#pragma once
#include "D:\Documents\School\DAE\Semester 4.5\Graphics Programming 2\OverlordEngine_x64\OverlordEngine\Misc\Material.h"

class DiffuseMaterial : public Material<DiffuseMaterial>
{
public:
	DiffuseMaterial();
	~DiffuseMaterial() override = default;

	DiffuseMaterial(const DiffuseMaterial& other) = delete;
	DiffuseMaterial(DiffuseMaterial&& other) noexcept = delete;
	DiffuseMaterial& operator=(const DiffuseMaterial& other) = delete;
	DiffuseMaterial& operator=(DiffuseMaterial&& other) noexcept = delete;

	void SetDiffuseTexture(const std::wstring& assetFile);

protected:
	void InitializeEffectVariables() override;

private:
	TextureData* m_pTextureData{};
};


#pragma once
#include "D:\Documents\School\DAE\Semester 4.5\Graphics Programming 2\OverlordEngine_x64\OverlordEngine\Misc\Material.h"

class UberMaterial : public Material<UberMaterial>
{
public:
	UberMaterial();
	~UberMaterial() override = default;

	UberMaterial(const UberMaterial& other) = delete;
	UberMaterial(UberMaterial&& other) = delete;
	UberMaterial& operator=(const UberMaterial& other) noexcept = delete;
	UberMaterial& operator=(UberMaterial&& other) noexcept = delete;

	XMFLOAT4 m_DiffuseColor{ 1, 0.5f, 0.5f, 1 };

	XMFLOAT4 m_SpecularColor{ 1.f, 1.f, 1.f, 1.f };
	float m_Shininess{ 80 };

	XMFLOAT4 m_AmbientColor{ 1.f, 1.f, 1.f, 1.f };
	float m_AmbientIntensity{ 0.5f };

	virtual void OnUpdateModelVariables(const SceneContext& /*sceneContext*/, const ModelComponent* /*pModel*/) const override;

protected:
	virtual void InitializeEffectVariables() override;

private:
	TextureData* m_pDiffuseTexture{};
	TextureData* m_pSpecularTexture{};
};


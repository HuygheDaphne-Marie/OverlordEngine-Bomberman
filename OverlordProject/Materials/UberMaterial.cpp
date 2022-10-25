#include "stdafx.h"
#include "UberMaterial.h"

UberMaterial::UberMaterial()
	: Material<UberMaterial>(L"Effects/UberShader.fx")
{
}

void UberMaterial::OnUpdateModelVariables(const SceneContext&, const ModelComponent*) const
{
	SetVariable_Texture(L"gTextureDiffuse", m_pDiffuseTexture);
	SetVariable_Vector(L"gColorDiffuse", m_DiffuseColor);

	SetVariable_Texture(L"gTextureSpecularIntensity", m_pSpecularTexture);
	SetVariable_Vector(L"gColorSpecular", m_SpecularColor);
	SetVariable_Scalar(L"gShininess", m_Shininess);

	SetVariable_Vector(L"gColorAmbient", m_AmbientColor);
	SetVariable_Scalar(L"gAmbientIntensity", m_AmbientIntensity);
}

void UberMaterial::InitializeEffectVariables()
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(L"Textures/Skulls_Diffusemap.tga");
	SetVariable_Texture(L"gTextureDiffuse", m_pDiffuseTexture);
	SetVariable_Vector(L"gColorDiffuse", m_DiffuseColor);

	m_pSpecularTexture = ContentManager::Load<TextureData>(L"Textures/Specular_Level.tga");
	SetVariable_Texture(L"gTextureSpecularIntensity", m_pSpecularTexture);
	SetVariable_Vector(L"gColorSpecular", m_SpecularColor);
	SetVariable_Scalar(L"gShininess", m_Shininess);

	SetVariable_Vector(L"gColorAmbient", m_AmbientColor);
	SetVariable_Scalar(L"gAmbientIntensity", m_AmbientIntensity);
}

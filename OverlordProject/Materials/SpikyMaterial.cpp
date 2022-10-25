#include "stdafx.h"
#include "SpikyMaterial.h"

SpikyMaterial::SpikyMaterial()
	: Material<SpikyMaterial>(L"Effects/SpikyShader.fx")
{
}

void SpikyMaterial::InitializeEffectVariables()
{
	SetVariable_Vector(L"gColorDiffuse", XMFLOAT4{ 0.823f, 0.2f, 0.2f, 1 });
	SetVariable_Vector(L"m_LightDirection", XMFLOAT3{ 0.577f, 1, 0 });
}

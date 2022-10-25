#include "stdafx.h"
#include "BackgroundTile.h"

#include "Materials/Shadow/DiffuseMaterial_Shadow.h"

BackgroundTile::BackgroundTile(const std::wstring& texturePath)
	: GameObject()
	, m_TexturePath{texturePath}
{
}

void BackgroundTile::Initialize(const SceneContext&)
{
	const auto pTileMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
	pTileMaterial->SetDiffuseTexture(m_TexturePath);

	const auto pUnitTileModel = new ModelComponent(L"Meshes/UnitPlane.ovm");
	pUnitTileModel->SetMaterial(pTileMaterial);

	AddComponent(pUnitTileModel);
}

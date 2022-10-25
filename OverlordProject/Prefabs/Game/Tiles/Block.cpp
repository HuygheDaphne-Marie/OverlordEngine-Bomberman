#include "stdafx.h"
#include "Block.h"

#include "Materials/Shadow/DiffuseMaterial_Shadow.h"
#include "Materials/DiffuseMaterial.h"
#include "Components/TileGridMap.h"

Block::Block(const XMINT2& coordinate, const XMFLOAT3& dimensions, const std::wstring& texturePath)
	: TileEntity(coordinate.x, coordinate.y)
	, m_Width(dimensions.x)
	, m_Height(dimensions.y)
	, m_Depth(dimensions.z)
	, m_TexturePath{texturePath}
{
}

void Block::Initialize(const SceneContext& sceneContext)
{
	TileEntity::Initialize(sceneContext);

	// Blocks are always blocking entities
	GridCoordinateComponent* pCoordinate = GetComponent<GridCoordinateComponent>();
	if (pCoordinate != nullptr)
	{
		pCoordinate->SetIsBlocking(true);
	}

	TileGridMap* pMap = GetScene()->FindGameObjectWithTag(TileGridMap::m_TagName)->GetComponent<TileGridMap>();

	GetTransform()->Scale(0.01f, 0.01f, 0.01f);
	if (pCoordinate != nullptr && pCoordinate->GetCoordinate().y < pMap->GetMapSize().y / 2)
		GetTransform()->Rotate(0.0f, -90.f, 0.0f);
	else
		GetTransform()->Rotate(0.0f, 90.f, 0.0f);
	
	// Shadows cause big performance drop in debug, fine in release however
#if NDEBUG
	DiffuseMaterial_Shadow* pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();
#else
	DiffuseMaterial* pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
#endif
	pMaterial->SetDiffuseTexture(m_TexturePath);

	bool castShadows = false;
#if NDEBUG
	castShadows = true;
#endif
	ModelComponent* pModelComp = AddComponent(new ModelComponent(L"Meshes/Block.ovm", castShadows));
	pModelComp->SetMaterial(pMaterial);

}

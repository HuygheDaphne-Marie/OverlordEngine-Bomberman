#include "stdafx.h"
#include "ModelTestScene.h"
#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial.h"

ModelTestScene::ModelTestScene()
	: GameScene(L"ModelTestScene")
{
}

void ModelTestScene::Initialize()
{
	auto& physX = PxGetPhysics();
	const auto pDefaultMaterial = physX.createMaterial(0.5f, 0.5f, 0.5f);

	m_pChair = new GameObject();
	m_pChair->GetTransform()->Translate(0, 1, 0);
	AddChild(m_pChair);

	// Materials
	//ColorMaterial* pMaterial = MaterialManager::Get()->CreateMaterial<ColorMaterial>();
	//pMaterial->SetColor(XMFLOAT4{ Colors::Red });
	DiffuseMaterial* pMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial>();
	pMaterial->SetDiffuseTexture(L"Textures/Chair_Dark.dds");

	ModelComponent* pModelComp = m_pChair->AddComponent(new ModelComponent(L"Meshes/Chair.ovm"));
	pModelComp->SetMaterial(pMaterial);

	RigidBodyComponent* pRb = m_pChair->AddComponent(new RigidBodyComponent);
	PxConvexMesh* pConvexMesh = ContentManager::Load<PxConvexMesh>(L"Meshes/Chair.ovpc");
	pRb->AddCollider(PxConvexMeshGeometry{ pConvexMesh }, *pDefaultMaterial);
	
	GameSceneExt::CreatePhysXGroundPlane(*this, pDefaultMaterial);
}

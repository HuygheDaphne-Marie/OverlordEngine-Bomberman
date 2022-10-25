#include "stdafx.h"
#include "UberMaterialScene.h"
#include "Materials/UberMaterial.h"

UberMaterialScene::UberMaterialScene()
	: GameScene(L"UberMaterialScene")
{
}

void UberMaterialScene::Initialize()
{
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.enableOnGUI = true;

	m_MatSphere = new GameObject();
	m_MatSphere->GetTransform()->Scale(20);
	AddChild(m_MatSphere);

	UberMaterial* pMaterial = MaterialManager::Get()->CreateMaterial<UberMaterial>();
	ModelComponent* pModel = m_MatSphere->AddComponent(new ModelComponent(L"Meshes/Sphere.ovm"));
	pModel->SetMaterial(pMaterial);

	m_pSphereMat = pMaterial;
}

void UberMaterialScene::OnGUI()
{
	//ImGui::ColorEdit4("Diffuse Color", ConvertUtil::ToImFloatPtr(m_pSphereMat->m_DiffuseColor));

	//ImGui::ColorEdit4("Specular Color", ConvertUtil::ToImFloatPtr(m_pSphereMat->m_SpecularColor));
	//ImGui::SliderFloat("Shininess", &(m_pSphereMat->m_Shininess), 0, 100);

	//ImGui::ColorEdit4("Ambient Color", ConvertUtil::ToImFloatPtr(m_pSphereMat->m_AmbientColor));
	//ImGui::SliderFloat("Ambient Intensity", &(m_pSphereMat->m_AmbientIntensity), 0, 1);

	//m_pSphereMat->OnUpdateModelVariables(GetSceneContext(), m_MatSphere->GetComponent<ModelComponent>());
	m_pSphereMat->DrawImGui();
}

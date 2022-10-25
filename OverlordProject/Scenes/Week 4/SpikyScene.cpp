#include "stdafx.h"
#include "SpikyScene.h"
#include "Materials/SpikyMaterial.h"

SpikyScene::SpikyScene()
	: GameScene(L"SpikyScene")
{
}

void SpikyScene::Initialize()
{
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.enableOnGUI = true;

	m_pBall = new GameObject();
	AddChild(m_pBall);
	m_pBall->GetTransform()->Scale(15.f);

	m_pMaterial = MaterialManager::Get()->CreateMaterial<SpikyMaterial>();
	ModelComponent* pModel = m_pBall->AddComponent(new ModelComponent(L"Meshes/OctaSphere.ovm"));
	pModel->SetMaterial(m_pMaterial);
	

}

void SpikyScene::OnGUI()
{
	m_pMaterial->DrawImGui();
}

void SpikyScene::Update()
{
	m_pBall->GetTransform()->Rotate(0, 20 * m_SceneContext.pGameTime->GetTotal(), 0);
}

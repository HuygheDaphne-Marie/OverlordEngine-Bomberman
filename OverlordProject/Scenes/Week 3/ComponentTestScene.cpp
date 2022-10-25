#include "stdafx.h"
#include "ComponentTestScene.h"

#include "Prefabs/Classes/SpherePrefab.h"

void ComponentTestScene::Initialize()
{
	//Defaults
	auto& physX = PxGetPhysics();
	const auto pBouncyMaterial = physX.createMaterial(0.f, 0.f, 1.f);

	//Ground Plane
	const auto pGroundActor = physX.createRigidStatic(PxTransform(PxQuat{PxPiDivTwo, PxVec3{0.f, 0.f, 1.f}}));
	PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{}, *pBouncyMaterial);
	GetPhysxProxy()->AddActor(*pGroundActor);

	//Sphere 1 (Group0 && Ignore Group1|Group2)
	GameObject* pSphere = new SpherePrefab(1.f, 10, XMFLOAT4{Colors::Red});
	pSphere->GetTransform()->Translate(0.f, 30.f, 0.f);

	RigidBodyComponent* pRigidBody = pSphere->AddComponent(new RigidBodyComponent);
	pRigidBody->AddCollider(PxSphereGeometry{ 1.f }, *pBouncyMaterial);
	pRigidBody->SetCollisionGroup(CollisionGroup::Group0);
	pRigidBody->SetCollisionIgnoreGroups(CollisionGroup::Group1 | CollisionGroup::Group2);
	AddChild(pSphere);

	//Sphere 2 (Group1)
	pSphere = new SpherePrefab(1.f, 10, XMFLOAT4{ Colors::Green });
	pSphere->GetTransform()->Translate(0.f, 20.f, 0.f);
	pRigidBody = pSphere->AddComponent(new RigidBodyComponent);
	pRigidBody->AddCollider(PxSphereGeometry{ 1.f }, *pBouncyMaterial);
	pRigidBody->SetCollisionGroup(CollisionGroup::Group1);
	AddChild(pSphere);

	//Sphere 3 (Group2)
	pSphere = new SpherePrefab(1.f, 10, XMFLOAT4{ Colors::Blue });
	pSphere->GetTransform()->Translate(0.f, 10.f, 0.f);
	pRigidBody = pSphere->AddComponent(new RigidBodyComponent);
	pRigidBody->AddCollider(PxSphereGeometry{ 1.f }, *pBouncyMaterial);
	pRigidBody->SetCollisionGroup(CollisionGroup::Group2);
	AddChild(pSphere);
}

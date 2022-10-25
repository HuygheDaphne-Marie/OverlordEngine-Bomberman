#include "stdafx.h"
#include "PongScene.h"
#include "Prefabs/Classes/CubePrefab.h"
#include "Prefabs/Classes/SpherePrefab.h"

PongScene::PongScene()
	: GameScene(L"PongScene")
{
}

void PongScene::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;
	m_SceneContext.settings.drawPhysXDebug = false;
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.clearColor = XMFLOAT4{ Colors::Black };

	//Defaults
	auto& physX = PxGetPhysics();
	const auto pBouncyMaterial = physX.createMaterial(0.f, 0.f, 1.f);

	// Camera
	{
		FixedCamera* pFixedCam = new FixedCamera();
		AddChild(pFixedCam);
		pFixedCam->GetTransform()->Translate(0, 50, 0);
		pFixedCam->GetTransform()->Rotate(90, 0, 0);
		SetActiveCamera(pFixedCam->GetComponent<CameraComponent>());
	}

	//Ground Plane
	{
		const auto pGroundActor = physX.createRigidStatic(PxTransform(PxQuat{ PxPiDivTwo, PxVec3{0.f, 0.f, 1.f} }));
		PxRigidActorExt::createExclusiveShape(*pGroundActor, PxPlaneGeometry{}, *pBouncyMaterial);
		GetPhysxProxy()->AddActor(*pGroundActor);
	}

	// Top & Bottom Colliders
	{
		const auto pTopCollider = physX.createRigidStatic(
			PxTransform{ 
				PxVec3{ 0, 0, m_HalfFieldSize/2 },
				PxQuat{ PxPiDivTwo, PxVec3{0.f, 1.f, 0.f} } 
			});
		PxRigidActorExt::createExclusiveShape(*pTopCollider, PxPlaneGeometry{}, *pBouncyMaterial);
		GetPhysxProxy()->AddActor(*pTopCollider);

		const auto pBottomCollider = physX.createRigidStatic(
			PxTransform{
				PxVec3{ 0, 0, -m_HalfFieldSize / 2 },
				PxQuat{ -PxPiDivTwo, PxVec3{0.f, 1.f, 0.f} }
			});
		PxRigidActorExt::createExclusiveShape(*pBottomCollider, PxPlaneGeometry{}, *pBouncyMaterial);
		GetPhysxProxy()->AddActor(*pBottomCollider);
	}

	// Out of bounds Triggers
	{
		const float triggerOffset = 5.f;
		auto triggerCallBack =
			std::bind(
				&PongScene::OnTrigger, this,
				std::placeholders::_1,
				std::placeholders::_2,
				std::placeholders::_3
			);

		// Left
		{
			m_pLeftTrigger = new GameObject();
			AddChild(m_pLeftTrigger);
			m_pLeftTrigger->GetTransform()->Translate(-(m_HalfFieldSize + triggerOffset), 0, 0);
			RigidBodyComponent* trigRb = m_pLeftTrigger->AddComponent(new RigidBodyComponent);
			trigRb->AddCollider(PxBoxGeometry{ 2.f, 2.f, m_HalfFieldSize }, *pBouncyMaterial, true);
			trigRb->SetKinematic(true);

			m_pLeftTrigger->SetOnTriggerCallBack(triggerCallBack);
		}

		// Right
		{
			m_pRightTrigger = new GameObject();
			AddChild(m_pRightTrigger);
			m_pRightTrigger->GetTransform()->Translate((m_HalfFieldSize + triggerOffset), 0, 0);
			RigidBodyComponent* trigRb = m_pRightTrigger->AddComponent(new RigidBodyComponent);
			trigRb->AddCollider(PxBoxGeometry{ 2.f, 2.f, m_HalfFieldSize }, *pBouncyMaterial, true);
			trigRb->SetKinematic(true);

			m_pRightTrigger->SetOnTriggerCallBack(triggerCallBack);
		}
	}

	XMFLOAT3 dimensions{ m_HalfPaddle.x * 2, m_HalfPaddle.y * 2, m_HalfPaddle.z * 2 };
	// Left Paddle
	{
		m_pLeftPaddle = new CubePrefab(dimensions, XMFLOAT4{ Colors::White });
		AddChild(m_pLeftPaddle);
		m_pLeftPaddle->GetTransform()->Translate(-m_HalfFieldSize, m_HalfPaddle.y + 0.01f, 0);

		RigidBodyComponent* pPaddleRb = m_pLeftPaddle->AddComponent(new RigidBodyComponent);
		pPaddleRb->AddCollider(PxBoxGeometry{ m_HalfPaddle.x, m_HalfPaddle.y, m_HalfPaddle.z }, *pBouncyMaterial);
		pPaddleRb->SetKinematic(true);

		// XZ plane constraint
		// RigidActor == null, seems like initialise isn't being called in time?
		// Only initialises when AddChild() is called
		auto d6Joint = PxD6JointCreate(physX, nullptr, PxTransform{ PxIdentity }, pPaddleRb->GetPxRigidActor(), PxTransform{ PxIdentity });
		d6Joint->setMotion(PxD6Axis::eZ, PxD6Motion::eFREE);

		InputAction up{ static_cast<int>(InputIds::KeyboardUp), InputState::down, 'W' };
		InputAction down{ static_cast<int>(InputIds::KeyboardDown), InputState::down, 'S' };

		GetSceneContext().pInput->AddInputAction(up);
		GetSceneContext().pInput->AddInputAction(down);
	}

	// Right Paddle
	{
		m_pRightPaddle = new CubePrefab(dimensions, XMFLOAT4{ Colors::White });
		AddChild(m_pRightPaddle);
		m_pRightPaddle->GetTransform()->Translate(m_HalfFieldSize, m_HalfPaddle.y + 0.01f, 0);

		RigidBodyComponent* pPaddleRb = m_pRightPaddle->AddComponent(new RigidBodyComponent);
		pPaddleRb->AddCollider(PxBoxGeometry{ m_HalfPaddle.x, m_HalfPaddle.y, m_HalfPaddle.z }, *pBouncyMaterial);
		pPaddleRb->SetKinematic(true);


		auto d6Joint = PxD6JointCreate(physX, nullptr, PxTransform{ PxIdentity }, pPaddleRb->GetPxRigidActor(), PxTransform{ PxIdentity });
		d6Joint->setMotion(PxD6Axis::eZ, PxD6Motion::eFREE);

		InputAction up{ static_cast<int>(InputIds::ArrowUp), InputState::down, VK_UP };
		InputAction down{ static_cast<int>(InputIds::ArrowDown), InputState::down, VK_DOWN };

		GetSceneContext().pInput->AddInputAction(up);
		GetSceneContext().pInput->AddInputAction(down);
	}

	// Ball
	{
		m_pBall = new SpherePrefab(1.f, 10, XMFLOAT4{ Colors::Red });
		AddChild(m_pBall);
		m_pBall->GetTransform()->Translate(0.f, 2.f, 0.f);

		RigidBodyComponent* pRigidBody = m_pBall->AddComponent(new RigidBodyComponent);
		pRigidBody->AddCollider(PxSphereGeometry{ 1.f }, *pBouncyMaterial);

		auto d6Joint = PxD6JointCreate(physX, nullptr, PxTransform{ PxIdentity }, pRigidBody->GetPxRigidActor(), PxTransform{ PxIdentity });
		d6Joint->setMotion(PxD6Axis::eX, PxD6Motion::eFREE);
		d6Joint->setMotion(PxD6Axis::eZ, PxD6Motion::eFREE);

		m_pBall->GetComponent<RigidBodyComponent>()->AddForce({ m_BallSpeed, 0, m_BallSpeed }, PxForceMode::eIMPULSE);
	}
}

void PongScene::Update()
{
	if (m_ShouldSceneReset)
	{
		ResetScene();
	}

	const float movementSpeed{ 5.f };
	const XMFLOAT3 upForce{ 0, 0, movementSpeed };
	const XMFLOAT3 downForce{ 0, 0, -movementSpeed };

	if (GetSceneContext().pInput->IsActionTriggered(static_cast<int>(InputIds::ArrowUp)))
	{
		XMFLOAT3 currPos = m_pRightPaddle->GetTransform()->GetPosition();
		currPos.z += movementSpeed * GetSceneContext().pGameTime->GetElapsed();
		m_pRightPaddle->GetTransform()->Translate(currPos);
	}
	if (GetSceneContext().pInput->IsActionTriggered(static_cast<int>(InputIds::ArrowDown)))
	{
		XMFLOAT3 currPos = m_pRightPaddle->GetTransform()->GetPosition();
		currPos.z -= movementSpeed * GetSceneContext().pGameTime->GetElapsed();
		m_pRightPaddle->GetTransform()->Translate(currPos);
	}

	if (GetSceneContext().pInput->IsActionTriggered(static_cast<int>(InputIds::KeyboardUp)))
	{
		XMFLOAT3 currPos = m_pLeftPaddle->GetTransform()->GetPosition();
		currPos.z += movementSpeed * GetSceneContext().pGameTime->GetElapsed();
		m_pLeftPaddle->GetTransform()->Translate(currPos);
	}
	if (GetSceneContext().pInput->IsActionTriggered(static_cast<int>(InputIds::KeyboardDown)))
	{
		XMFLOAT3 currPos = m_pLeftPaddle->GetTransform()->GetPosition();
		currPos.z -= movementSpeed * GetSceneContext().pGameTime->GetElapsed();
		m_pLeftPaddle->GetTransform()->Translate(currPos);
	}
}

void PongScene::Draw()
{
}

void PongScene::OnGUI()
{
	ImGui::Text("Left paddle: W & S");
	ImGui::Text("Right paddle: Up arrow & Down arrow");
}

void PongScene::OnTrigger(GameObject* pTriggerObject, GameObject* pOtherObject, PxTriggerAction action)
{
	// Queue SceneReset
	if (action == PxTriggerAction::ENTER && 
		pOtherObject == m_pBall && 
		pTriggerObject == m_pLeftTrigger || pTriggerObject == m_pRightTrigger)
	{
		m_ShouldSceneReset = true;
	}
}

void PongScene::ResetScene()
{
	m_pLeftPaddle->GetTransform()->Translate(-m_HalfFieldSize, m_HalfPaddle.y + 0.01f, 0);
	m_pRightPaddle->GetTransform()->Translate(m_HalfFieldSize, m_HalfPaddle.y + 0.01f, 0);

	// Reset Ball
	m_pBall->GetTransform()->Translate(0, 0, 0);
	m_pBall->GetComponent<RigidBodyComponent>()->AddForce({ m_BallSpeed, 0, m_BallSpeed }, PxForceMode::eIMPULSE);

	m_ShouldSceneReset = false;
}

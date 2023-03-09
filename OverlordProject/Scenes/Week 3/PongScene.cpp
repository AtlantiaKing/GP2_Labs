#include "stdafx.h"
#include "PongScene.h"

#include "Prefabs/CubePrefab.h"
#include "Prefabs/SpherePrefab.h"

void PongScene::Initialize()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	auto prevCam{ m_SceneContext.pCamera };
	auto pCamera = new FixedCamera{};
	AddChild(pCamera);
	SetActiveCamera(pCamera->GetComponent<CameraComponent>());
	RemoveChild(prevCam->GetGameObject());
	pCamera->GetTransform()->Translate(0.0f, 0.0f, -50.0f);

	auto& physX{ PxGetPhysics() };
	auto pPhysMat{ physX.createMaterial(0.0f, 0.0f, 1.0f) };

	const XMFLOAT3 peddleDimensions{ 1.0f, 5.0f, 1.0f };
	const XMFLOAT3 peddlePosition{ 30.0f, 0.0f, 0.0f };
	const PxBoxGeometry peddleGeo{ peddleDimensions.x / 2.0f, peddleDimensions.y / 2.0f, peddleDimensions.z / 2.0f };


	// Right peddle
	m_pRightPeddle = new CubePrefab{ peddleDimensions };
	AddChild(m_pRightPeddle);
	m_pRightPeddle->GetTransform()->Translate(XMVECTOR{ peddlePosition.x, peddlePosition.y, peddlePosition.z });
	auto pRightRb = m_pRightPeddle->AddComponent(new RigidBodyComponent{});
	pRightRb->SetKinematic(true);
	pRightRb->AddCollider(peddleGeo, *pPhysMat);

	// Left peddle
	m_pLeftPeddle = new CubePrefab{ peddleDimensions };
	AddChild(m_pLeftPeddle);
	m_pLeftPeddle->GetTransform()->Translate(XMVECTOR{ -peddlePosition.x, peddlePosition.y, peddlePosition.z });
	auto pLeftRb{ m_pLeftPeddle->AddComponent(new RigidBodyComponent{}) };
	pLeftRb->SetKinematic(true);
	pLeftRb->AddCollider(peddleGeo, *pPhysMat);

	// Ball
	m_pBall = new SpherePrefab{ 0.5f, 10, XMFLOAT4{ Colors::Red } };
	AddChild(m_pBall);
	auto pBallRb = m_pBall->AddComponent(new RigidBodyComponent{});
	pBallRb->AddCollider(PxSphereGeometry{ 0.5f }, *pPhysMat);
	pBallRb->SetConstraint(RigidBodyConstraint::TransZ, false);
	pBallRb->SetConstraint(RigidBodyConstraint::AllRot, false);

	constexpr float ballSpeed{ 20.0f };
	const XMFLOAT3 direction
	{
		rand() % 1001 / 1000.0f - 0.5f,
		rand() % 1001 / 1000.0f - 0.5f,
		0.0f
	};
	PxVec3 directionVector(direction.x, direction.y, direction.z);
	directionVector.normalize();
	directionVector *= ballSpeed;

	pBallRb->AddForce(XMFLOAT3(directionVector.x, directionVector.y, directionVector.z), PxForceMode::eIMPULSE);

	const XMFLOAT3 horizontalPos{ 0.0f, 20.0f, 0.0f };
	const PxBoxGeometry horizontalBox{ 40.0f, 0.5f, 0.5f };

	// Top collider
	auto pTopBar{ new GameObject{} };
	AddChild(pTopBar);
	pTopBar->GetTransform()->Translate(horizontalPos);
	pTopBar->AddComponent(new RigidBodyComponent(true))->AddCollider(horizontalBox, *pPhysMat);

	// Bottom collider
	auto pBottomBar{ new GameObject{} };
	AddChild(pBottomBar);
	pBottomBar->GetTransform()->Translate(horizontalPos.x, -horizontalPos.y, horizontalPos.z);
	pBottomBar->AddComponent(new RigidBodyComponent(true))->AddCollider(horizontalBox, *pPhysMat);

	const XMFLOAT3 verticalPos{ 35.0f, 0.0f, 0.0f };
	const PxBoxGeometry verticalBox{ 0.5f, 20.0f, 0.5f };

	// Right collider
	auto pRightBar{ new GameObject{} };
	AddChild(pRightBar);
	pRightBar->GetTransform()->Translate(verticalPos);
	pRightBar->AddComponent(new RigidBodyComponent(true))->AddCollider(verticalBox, *pPhysMat, true);

	pRightBar->SetOnTriggerCallBack([=](GameObject*, GameObject* pOther, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER && pOther == m_pBall)
			{
				Reset();
			}
		});

	// Left collider
	auto pLeftBar{ new GameObject{} };
	AddChild(pLeftBar);
	pLeftBar->GetTransform()->Translate(-verticalPos.x, verticalPos.y, verticalPos.z);
	pLeftBar->AddComponent(new RigidBodyComponent(true))->AddCollider(verticalBox, *pPhysMat, true);

	pLeftBar->SetOnTriggerCallBack([=](GameObject*, GameObject* pOther, PxTriggerAction action)
		{
			if (action == PxTriggerAction::ENTER && pOther == m_pBall)
			{
				Reset();
			}
		});
}

void PongScene::PostInitialize()
{
	m_pBall->GetComponent<RigidBodyComponent>()->GetPxRigidActor()->setActorFlags(PxActorFlag::eDISABLE_GRAVITY);
	m_pLeftPeddle->GetComponent<RigidBodyComponent>()->GetPxRigidActor()->setActorFlags(PxActorFlag::eDISABLE_GRAVITY);
	m_pRightPeddle->GetComponent<RigidBodyComponent>()->GetPxRigidActor()->setActorFlags(PxActorFlag::eDISABLE_GRAVITY);
}

void PongScene::Update()
{
	constexpr float peddleMoveSpeed{ 20.0f };
	constexpr float maxPos{ 17.0f };

	auto pRightTransform{ m_pRightPeddle->GetTransform() };
	XMFLOAT3 rightPos{ pRightTransform->GetPosition() };
	if (InputManager::IsKeyboardKey(InputState::down, VK_UP))
	{
		rightPos.y += peddleMoveSpeed * m_SceneContext.pGameTime->GetElapsed();
		if (rightPos.y < maxPos) pRightTransform->Translate(rightPos);
	}
	else if (InputManager::IsKeyboardKey(InputState::down, VK_DOWN))
	{
		rightPos.y -= peddleMoveSpeed * m_SceneContext.pGameTime->GetElapsed();
		if (rightPos.y > -maxPos) pRightTransform->Translate(rightPos);
	}

	auto pleftTransform{ m_pLeftPeddle->GetTransform() };
	XMFLOAT3 leftPos{ pleftTransform->GetPosition() };
	if (InputManager::IsKeyboardKey(InputState::down, 'W') || InputManager::IsKeyboardKey(InputState::down, 'Z'))
	{
		leftPos.y += peddleMoveSpeed * m_SceneContext.pGameTime->GetElapsed();
		if (leftPos.y < maxPos) pleftTransform->Translate(leftPos);
	}
	else if (InputManager::IsKeyboardKey(InputState::down, 'S'))
	{
		leftPos.y -= peddleMoveSpeed * m_SceneContext.pGameTime->GetElapsed();
		if (leftPos.y > -maxPos) pleftTransform->Translate(leftPos);
	}

	if (InputManager::IsKeyboardKey(InputState::pressed, 'R'))
	{
		Reset();
	}

	if (m_MustReset)
	{
		constexpr float ballSpeed{ 20.0f };
		const XMFLOAT3 direction
		{
			rand() % 1001 / 1000.0f - 0.5f,
			rand() % 1001 / 1000.0f - 0.5f,
			0.0f
		};
		PxVec3 directionVector(direction.x, direction.y, direction.z);
		directionVector.normalize();
		directionVector *= ballSpeed;

		m_pBall->GetComponent<RigidBodyComponent>()->AddForce(XMFLOAT3(directionVector.x, directionVector.y, directionVector.z), PxForceMode::eIMPULSE);

		m_MustReset = false;
	}
}

void PongScene::Draw()
{
}

void PongScene::OnGUI()
{
}

void PongScene::Reset()
{
	m_pBall->GetTransform()->Translate(0.0f, 0.0f, 0.0f);

	m_MustReset = true;

	const XMFLOAT3 peddlePosition{ 30.0f, 0.0f, 0.0f };
	m_pRightPeddle->GetTransform()->Translate(XMVECTOR{ peddlePosition.x, peddlePosition.y, peddlePosition.z });
	m_pLeftPeddle->GetTransform()->Translate(XMVECTOR{ -peddlePosition.x, peddlePosition.y, peddlePosition.z });
}

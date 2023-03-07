#include "stdafx.h"
#include "PongScene.h"

#include "Prefabs/CubePrefab.h"
#include "Prefabs/SpherePrefab.h"

void PongScene::Initialize()
{
	auto& physX{ PxGetPhysics() };
	auto pPhysMat{ physX.createMaterial(0.5f, 0.5f, 0.5f) };

	const XMFLOAT3 peddleDimensions{ 1.0f, 5.0f, 1.0f };
	const XMFLOAT3 peddlePosition{ 30.0f, 0.0f, 0.0f };
	const PxBoxGeometry peddleGeo{ peddleDimensions.x / 2.0f, peddleDimensions.y / 2.0f, peddleDimensions.z / 2.0f };

	m_pRightPeddle = new CubePrefab{ peddleDimensions };
	AddChild(m_pRightPeddle);
	m_pRightPeddle->GetTransform()->Translate(XMVECTOR{ peddlePosition.x, peddlePosition.y, peddlePosition.z });
	auto pRightRb = m_pRightPeddle->AddComponent(new RigidBodyComponent{});
	pRightRb->SetKinematic(true);
	pRightRb->AddCollider(peddleGeo, *pPhysMat);

	m_pLeftPeddle = new CubePrefab{ peddleDimensions };
	AddChild(m_pLeftPeddle);
	m_pLeftPeddle->GetTransform()->Translate(XMVECTOR{ -peddlePosition.x, peddlePosition.y, peddlePosition.z });
	auto pLeftRb{ m_pLeftPeddle->AddComponent(new RigidBodyComponent{}) };
	pLeftRb->SetKinematic(true);
	pLeftRb->AddCollider(peddleGeo, *pPhysMat);

	m_pBall = new SpherePrefab{ 0.5f, 10, XMFLOAT4{ Colors::Red } };
	AddChild(m_pBall);
	auto pBallRb = m_pBall->AddComponent(new RigidBodyComponent{});
	pBallRb->SetKinematic(true);
	pBallRb->AddCollider(PxSphereGeometry{ 0.5f }, *pPhysMat);

	srand(static_cast<unsigned int>(time(nullptr)));

	m_BallDirection = XMFLOAT3(cosf(rand() % 1001 / 1000.0f), sinf(rand() % 1001 / 1000.0f), 0.0f);
}

void PongScene::Update()
{
	constexpr float ballMoveSpeed{ 20.0f };

	const XMFLOAT3 curPos{ m_pBall->GetTransform()->GetPosition() };
	const XMVECTOR newPos
	{ 
		curPos.x + m_BallDirection.x * ballMoveSpeed * m_SceneContext.pGameTime->GetElapsed(),
		curPos.y + m_BallDirection.y * ballMoveSpeed * m_SceneContext.pGameTime->GetElapsed(),
		curPos.z + m_BallDirection.z * ballMoveSpeed * m_SceneContext.pGameTime->GetElapsed()
	};
	m_pBall->GetTransform()->Translate(newPos);
}

void PongScene::Draw()
{
}

void PongScene::OnGUI()
{
}

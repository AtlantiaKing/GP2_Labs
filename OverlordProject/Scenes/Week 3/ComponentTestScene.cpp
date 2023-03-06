#include "stdafx.h"
#include "ComponentTestScene.h"
#include "Prefabs/SpherePrefab.h"

void ComponentTestScene::Initialize()
{
	auto& physX{ PxGetPhysics() };
	auto pBouncyMaterial{ physX.createMaterial(0.5f, 0.5f, 1.0f) };

	// Ground plane
	GameSceneExt::CreatePhysXGroundPlane(*this, pBouncyMaterial);

	// Sphere red (Group 0)
	auto pSphere{ new SpherePrefab{ 1.0f, 10, XMFLOAT4{ Colors::Red } } };
	AddChild(pSphere);

	pSphere->GetTransform()->Translate(0.0f, 30.0f, 0.0f);
	auto pRigidBody{ pSphere->AddComponent(new RigidBodyComponent()) };
	pRigidBody->AddCollider(PxSphereGeometry{ 1.0f }, *pBouncyMaterial);
	pRigidBody->SetCollisionGroup(CollisionGroup::Group0);
	pRigidBody->SetCollisionIgnoreGroups(CollisionGroup::Group1 | CollisionGroup::Group2);

	// Sphere green (Group 1)
	pSphere = new SpherePrefab{ 1.0f, 10, XMFLOAT4{ Colors::Green } };
	AddChild(pSphere);

	pSphere->GetTransform()->Translate(0.5f, 20.0f, 0.0f);
	pRigidBody = pSphere->AddComponent(new RigidBodyComponent());
	pRigidBody->AddCollider(PxSphereGeometry{ 1.0f }, *pBouncyMaterial);
	pRigidBody->SetCollisionGroup(CollisionGroup::Group1);
	pRigidBody->SetConstraint(RigidBodyConstraint::TransX | RigidBodyConstraint::TransZ, false);

	// Sphere green (Group 2)
	pSphere = new SpherePrefab{ 1.0f, 10, XMFLOAT4{ Colors::Blue } };
	AddChild(pSphere);

	pSphere->GetTransform()->Translate(0.0f, 10.0f, 0.0f);
	pRigidBody = pSphere->AddComponent(new RigidBodyComponent());
	pRigidBody->AddCollider(PxSphereGeometry{ 1.0f }, *pBouncyMaterial);
	pRigidBody->SetCollisionGroup(CollisionGroup::Group2);
}

void ComponentTestScene::Update()
{
}

void ComponentTestScene::Draw()
{
}

void ComponentTestScene::OnGUI()
{
}

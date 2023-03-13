#include "stdafx.h"
#include "ModelTestScene.h"
#include "Materials/DiffuseMaterial.h"

void ModelTestScene::Initialize()
{
	// Get physics
	auto& physX{ PxGetPhysics() };

	// Create a physics materials
	auto pPhysMat{ physX.createMaterial(0.5f, 0.5f, 0.5f) };

	// Create a chair GO
	GameObject* pChair{ new GameObject{} };
	AddChild(pChair);

	// Create a material
	DiffuseMaterial* pMaterial{ MaterialManager::Get()->CreateMaterial<DiffuseMaterial>() };
	pMaterial->SetDiffuseTexture(L"Textures/Chair_Dark.dds");

	// Add a model component and assign the material
	pChair->AddComponent(new ModelComponent{ L"Meshes/Chair.ovm" })->SetMaterial(pMaterial);

	// Move the chair
	pChair->GetComponent<TransformComponent>()->Translate(0.0f, 10.0f, 0.0f);

	// Create a convex geometry of the chair
	const auto pConvexMesh = ContentManager::Load<PxConvexMesh>(L"Meshes/Chair.ovpc");
	const auto convexGeometry{ PxConvexMeshGeometry{ pConvexMesh } };

	// Add a rigidbody and assign a collider with the convex geometry
	pChair->AddComponent(new RigidBodyComponent())->AddCollider(convexGeometry, *pPhysMat);

	//Ground Plane
	GameSceneExt::CreatePhysXGroundPlane(*this, pPhysMat);
}

void ModelTestScene::Update()
{
}

void ModelTestScene::Draw()
{
}

void ModelTestScene::OnGUI()
{
}

#include "stdafx.h"
#include "UberMaterialScene.h"

#include "Materials/SkullUberMaterial.h"
#include "Materials/BricksUberMaterial.h"

void UberMaterialScene::Initialize()
{
	// Create uber materials
	m_pSkullMaterial = MaterialManager::Get()->CreateMaterial<SkullUberMaterial>();
	m_pBricksMaterial = MaterialManager::Get()->CreateMaterial<BricksUberMaterial>();

	// Create a sphere GO
	GameObject* pSphere{ new GameObject{} };
	AddChild(pSphere);

	// Add a model component and assign the material
	pSphere->AddComponent(new ModelComponent{ L"Meshes/Sphere.ovm" })->SetMaterial(m_pSkullMaterial);

	// Scale the sphere
	TransformComponent* pSphereTransform{ pSphere->GetComponent<TransformComponent>() };
	pSphereTransform->Scale(30.0f, 30.0f, 30.0f);
	pSphereTransform->Translate(25.0f, 0.0f, 0.0f);

	// Create a chair GO
	GameObject* pChair{ new GameObject{} };
	AddChild(pChair);

	// Add a model component and assign the material
	pChair->AddComponent(new ModelComponent{ L"Meshes/Chair.ovm" })->SetMaterial(m_pBricksMaterial);

	// Scale the sphere
	TransformComponent* pChairTransform{ pChair->GetComponent<TransformComponent>() };
	pChairTransform->Scale(4.0f, 4.0f, 4.0f);
	pChairTransform->Translate(-25.0f, -10.0f, -10.0f);

	// Disable the grid and enable ImGui
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.enableOnGUI = true;
}

void UberMaterialScene::Update()
{
}

void UberMaterialScene::Draw()
{
}

void UberMaterialScene::OnGUI()
{
	m_pSkullMaterial->DrawImGui();
	m_pBricksMaterial->DrawImGui();
}

#include "stdafx.h"
#include "SpikyScene.h"
#include <Materials/SpikyMaterial.h>

void SpikyScene::Initialize()
{
	// Create a new GO
	GameObject* pSphere{ new GameObject{} };
	AddChild(pSphere);

	// Create a red material
	m_pMaterial = MaterialManager::Get()->CreateMaterial<SpikyMaterial>();

	// Add a model and assign the material
	pSphere->AddComponent(new ModelComponent{ L"Meshes/OctaSphere.ovm" })->SetMaterial(m_pMaterial);

	// Cache the transform and scale it
	m_pTransform = pSphere->GetComponent<TransformComponent>();
	m_pTransform->Scale(15.0f);

	// Disable the grid and enable ImGui
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.enableOnGUI = true;
}

void SpikyScene::Update()
{
	constexpr float rotateSpeed{ 20.0f };

	// Rotate the spiky ball
	m_pTransform->Rotate(0.0f, m_SceneContext.pGameTime->GetTotal() * rotateSpeed, 0.0f);
}

void SpikyScene::Draw()
{
}

void SpikyScene::OnGUI()
{
	m_pMaterial->DrawImGui();
}

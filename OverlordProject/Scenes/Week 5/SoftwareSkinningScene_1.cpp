#include "stdafx.h"
#include "SoftwareSkinningScene_1.h"
#include "Materials/ColorMaterial.h"
#include "Prefabs/BoneObject.h"

void SoftwareSkinningScene_1::Initialize()
{
	m_SceneContext.settings.enableOnGUI = true;

	// Create a material for the bones
	ColorMaterial* pMaterial{ MaterialManager::Get()->CreateMaterial<ColorMaterial>() };
	pMaterial->SetColor(XMFLOAT4{ 0.5f, 0.5f, 0.5f, 1.0f });

	// Create a root object for the scene
	GameObject* pRoot{ new GameObject{} };
	AddChild(pRoot);

	constexpr float boneSize{ 15.f };

	// Initialize the first bone object
	m_pBone0 = new BoneObject{ pMaterial, boneSize };
	pRoot->AddChild(m_pBone0);

	// Initialize the second bone object
	m_pBone1 = new BoneObject{ pMaterial, boneSize };
	m_pBone0->AddBone(m_pBone1);
}

void SoftwareSkinningScene_1::Update()
{
	if (m_AutoRotate)
	{
		constexpr float rotationSpeed{ 45.0f };
		constexpr float maxAngle{ 45.0f };
		m_BoneRotation += rotationSpeed * m_RotationSign * m_SceneContext.pGameTime->GetElapsed();

		if (abs(m_BoneRotation) > maxAngle)
		{
			m_BoneRotation -= m_RotationSign * (abs(m_BoneRotation) - maxAngle);
			m_RotationSign = -m_RotationSign;
		}

		m_Bone0Rot = XMFLOAT3{ 0.0f, 0.0f, m_BoneRotation };
		m_Bone1Rot = XMFLOAT3{ 0.0f, 0.0f, -m_BoneRotation * 2.0f };
	}

	m_pBone0->GetTransform()->Rotate(m_Bone0Rot);
	m_pBone1->GetTransform()->Rotate(m_Bone1Rot);

}

void SoftwareSkinningScene_1::OnGUI()
{
	ImGui::BeginDisabled(m_AutoRotate);
	ImGui::DragFloat3("Bone 0 - ROT", reinterpret_cast<float*>(&m_Bone0Rot));
	ImGui::DragFloat3("Bone 1 - ROT", reinterpret_cast<float*>(&m_Bone1Rot));
	ImGui::EndDisabled();

	ImGui::Checkbox("Auto Rotate", &m_AutoRotate);
}

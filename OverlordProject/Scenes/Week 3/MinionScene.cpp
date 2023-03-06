//Precompiled Header [ALWAYS ON TOP IN CPP]
#include "stdafx.h"
#include "MinionScene.h"

#include "Prefabs/TorusPrefab.h"


MinionScene::MinionScene() :
	GameScene(L"MinionScene"){}

void MinionScene::Initialize()
{
	//m_SceneContext.settings.showInfoOverlay = true;
	//m_SceneContext.settings.drawPhysXDebug = true;
	//m_SceneContext.settings.drawGrid = true;
	m_SceneContext.settings.enableOnGUI = true;

	Logger::LogInfo(L"Welcome, humble Minion!");

	// Torus big
	m_pTorusBig = new TorusPrefab{ 10, 50, 1, 20, XMFLOAT4{ Colors::Red } };
	AddChild(m_pTorusBig);

	// Torus medium
	m_pTorusMedium = new TorusPrefab{ 7, 50, 1, 20, XMFLOAT4{ Colors::Green } };
	m_pTorusBig->AddChild(m_pTorusMedium);

	// Torus small
	m_pTorusSmall = new TorusPrefab{ 4, 50, 1, 20, XMFLOAT4{ Colors::Blue } };
	m_pTorusMedium->AddChild(m_pTorusSmall);
}

void MinionScene::Update()
{
	const float rotation{ 90.0f * m_SceneContext.pGameTime->GetTotal() };
	m_pTorusBig->GetTransform()->Rotate(0.0f, rotation, 0.0f);
	m_pTorusMedium->GetComponent<TransformComponent>()->Rotate(rotation, 0.0f, 0.0f);
	m_pTorusSmall->GetTransform()->Rotate(0.0f, rotation, 0.0f);
}

void MinionScene::Draw()
{
	//Optional
}

void MinionScene::OnGUI()
{
	ImGui::Text("This only activates if\n SceneSettings.enableOnGUI is True.\n\n");
	ImGui::Text("Use ImGui to add custom\n controllable scene parameters!");
	ImGui::ColorEdit3("Demo ClearColor", &m_SceneContext.settings.clearColor.x, ImGuiColorEditFlags_NoInputs);
}

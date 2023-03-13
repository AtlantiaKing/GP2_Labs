#pragma once

class SkullUberMaterial;
class BricksUberMaterial;

class UberMaterialScene final : public GameScene
{
public:
	UberMaterialScene() : GameScene(L"Uber Material Scene") {};
	~UberMaterialScene() override = default;

	UberMaterialScene(const UberMaterialScene& other) = delete;
	UberMaterialScene(UberMaterialScene&& other) noexcept = delete;
	UberMaterialScene& operator=(const UberMaterialScene& other) = delete;
	UberMaterialScene& operator=(UberMaterialScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;

private:
	SkullUberMaterial* m_pSkullMaterial{};
	BricksUberMaterial* m_pBricksMaterial{};
};
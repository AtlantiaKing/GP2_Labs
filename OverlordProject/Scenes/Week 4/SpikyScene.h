#pragma once

class SpikyMaterial;

class SpikyScene final : public GameScene
{
public:
	SpikyScene() : GameScene(L"Model Test Scene") {};
	~SpikyScene() override = default;

	SpikyScene(const SpikyScene& other) = delete;
	SpikyScene(SpikyScene&& other) noexcept = delete;
	SpikyScene& operator=(const SpikyScene& other) = delete;
	SpikyScene& operator=(SpikyScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;

private:
	TransformComponent* m_pTransform{};
	SpikyMaterial* m_pMaterial{};
};



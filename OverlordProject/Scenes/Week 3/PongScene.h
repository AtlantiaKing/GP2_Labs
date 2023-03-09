#pragma once

class CubePrefab;
class SpherePrefab;

class PongScene final : public GameScene
{
public:
	PongScene() : GameScene(L"Pong Scene") {};
	~PongScene() override = default;

	PongScene(const PongScene& other) = delete;
	PongScene(PongScene&& other) noexcept = delete;
	PongScene& operator=(const PongScene& other) = delete;
	PongScene& operator=(PongScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void PostInitialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;

private:
	bool m_MustReset{};

	CubePrefab* m_pRightPeddle{};
	CubePrefab* m_pLeftPeddle{};
	SpherePrefab* m_pBall{};

	void Reset();
};


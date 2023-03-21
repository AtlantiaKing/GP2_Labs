#pragma once

class BoneObject;

class SoftwareSkinningScene_1 final : public GameScene
{
public:
	SoftwareSkinningScene_1() : GameScene(L"Software Skinning Scene 1") {};
	~SoftwareSkinningScene_1() override = default;

	SoftwareSkinningScene_1(const SoftwareSkinningScene_1& other) = delete;
	SoftwareSkinningScene_1(SoftwareSkinningScene_1&& other) noexcept = delete;
	SoftwareSkinningScene_1& operator=(const SoftwareSkinningScene_1& other) = delete;
	SoftwareSkinningScene_1& operator=(SoftwareSkinningScene_1&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void OnGUI() override;

private:
	BoneObject* m_pBone0{}, * m_pBone1{};

	float m_BoneRotation{};
	int m_RotationSign{ 1 };

	bool m_AutoRotate{ true };
	XMFLOAT3 m_Bone0Rot{};
	XMFLOAT3 m_Bone1Rot{};
};


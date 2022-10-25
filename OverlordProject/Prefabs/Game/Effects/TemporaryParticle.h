#pragma once
#include "..\OverlordEngine\Scenegraph\GameObject.h"

class TemporaryParticle : public GameObject
{
public:
	TemporaryParticle(const XMFLOAT3& pos, const std::wstring& assetFile, const ParticleEmitterSettings& emitterSettings, UINT particleCount = 50, float lifeTime = -1.f);
	~TemporaryParticle() override = default;
	TemporaryParticle(const TemporaryParticle& other) = delete;
	TemporaryParticle(TemporaryParticle&& other) noexcept = delete;
	TemporaryParticle& operator=(const TemporaryParticle& other) = delete;
	TemporaryParticle& operator=(TemporaryParticle&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	float m_LifeTime{};
	const XMFLOAT3 m_SpawnPos{};

	// Emitter settings
	const std::wstring m_AssetFile{};
	const ParticleEmitterSettings m_EmitterSettings{};
	const UINT m_ParticleCount{};
};


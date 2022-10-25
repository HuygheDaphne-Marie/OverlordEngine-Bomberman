#include "stdafx.h"
#include "TemporaryParticle.h"

TemporaryParticle::TemporaryParticle(const XMFLOAT3& pos, const std::wstring& assetFile, 
	const ParticleEmitterSettings& emitterSettings, UINT particleCount, float lifeTime)
	: GameObject{}
	, m_SpawnPos{ pos }
	, m_AssetFile{ assetFile }
	, m_EmitterSettings{ emitterSettings }
	, m_ParticleCount{ particleCount }
{
	if (lifeTime <= -0.01f)
		m_LifeTime = emitterSettings.maxEnergy; // if left default/negative then use the setting one instead
	else
		m_LifeTime = lifeTime;
}

void TemporaryParticle::Initialize(const SceneContext& /*sceneContext*/)
{
	GetTransform()->Translate(m_SpawnPos);
	AddComponent(new ParticleEmitterComponent(m_AssetFile, m_EmitterSettings, m_ParticleCount));
}

void TemporaryParticle::Update(const SceneContext& sceneContext)
{
	if (m_LifeTime <= 0.0f)
		GetScene()->RemoveChild(this, true);
	else
		m_LifeTime -= sceneContext.pGameTime->GetElapsed();
}

#include "stdafx.h"
#include "BombExplosion.h"


//minSize = 1.f;
//maxSize = 2.f;
// 
//minEnergy = 1.f;
//maxEnergy = 2.f;
// 
//minEmitterRadius = .2f;
//maxEmitterRadius = .5f;
// 
//minScale = 3.5f;
//maxScale = 5.5f;
//
//velocity = { 0.f,6.f,0.f };
//color = { 1.f,1.f,1.f, .6f };

UINT BombExplosion::m_ParticleCount{ 50 };
std::wstring BombExplosion::m_AssetPath{ L"Textures/circle.png" };
ParticleEmitterSettings BombExplosion::m_ParticleSettings
{
	0.2f,
	0.3f,

	0.2f,
	0.5f,

	0.2f,
	0.5f,

	1.5f,
	3.5f,

	{ 0.f, 0.f, 0.f },
	XMFLOAT4{ Colors::Yellow }
};

BombExplosion::BombExplosion(const XMFLOAT3& pos)
	: TemporaryParticle(pos, m_AssetPath, m_ParticleSettings, m_ParticleCount)
{
}

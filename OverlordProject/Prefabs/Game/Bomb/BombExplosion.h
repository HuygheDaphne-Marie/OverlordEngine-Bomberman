#pragma once
#include "Prefabs/Game/Effects/TemporaryParticle.h"

/*
This is more of a prefab variant than anything else, 
I didn't want to define a bunch of unrelated variables in the 'Bomb' class

So instead, they can just spawn one of these
*/

class BombExplosion : public TemporaryParticle
{
public:
	BombExplosion(const XMFLOAT3& pos);
	~BombExplosion() override = default;
	BombExplosion(const BombExplosion & other) = delete;
	BombExplosion(BombExplosion && other) noexcept = delete;
	BombExplosion& operator=(const BombExplosion & other) = delete;
	BombExplosion& operator=(BombExplosion && other) noexcept = delete;

private:
	static std::wstring m_AssetPath;
	static ParticleEmitterSettings m_ParticleSettings;
	static UINT m_ParticleCount;
};


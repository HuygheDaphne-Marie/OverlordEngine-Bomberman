#pragma once
#include "D:\Documents\School\DAE\Semester 4.5\Graphics Programming 2\OverlordEngine_x64\OverlordEngine\Misc\Material.h"

class SpikyMaterial : public Material<SpikyMaterial>
{
public:
	SpikyMaterial();
	~SpikyMaterial() override = default;

	SpikyMaterial(const SpikyMaterial& other) = delete;
	SpikyMaterial(SpikyMaterial&& other) noexcept = delete;
	SpikyMaterial& operator=(const SpikyMaterial& other) = delete;
	SpikyMaterial& operator=(SpikyMaterial&& other) noexcept = delete;

protected:
	void InitializeEffectVariables() override;
};


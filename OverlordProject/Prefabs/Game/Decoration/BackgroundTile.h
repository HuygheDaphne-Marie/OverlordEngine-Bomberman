#pragma once
#include "..\OverlordEngine\Scenegraph\GameObject.h"

class BackgroundTile : public GameObject
{
public:
	BackgroundTile(const std::wstring& texturePath);
	~BackgroundTile() override = default;
	BackgroundTile(const BackgroundTile& other) = delete;
	BackgroundTile(BackgroundTile&& other) noexcept = delete;
	BackgroundTile& operator=(const BackgroundTile& other) = delete;
	BackgroundTile& operator=(BackgroundTile&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext&) override;

private:
	const std::wstring m_TexturePath{};
};


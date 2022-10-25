#pragma once
#include "..\OverlordEngine\Scenegraph\GameObject.h"
#include "Components/PlayerPickupManager.h"
class Player;
class SpriteList;

class PlayerUI : public GameObject
{
public:
	static const int m_SpriteStep;

	PlayerUI(Player* pBoundPlayer, const XMFLOAT2& pos, bool alignDown = true, bool alignLeft = true);
	~PlayerUI() override = default;
	PlayerUI(const PlayerUI & other) = delete;
	PlayerUI(PlayerUI && other) noexcept = delete;
	PlayerUI& operator=(const PlayerUI & other) = delete;
	PlayerUI& operator=(PlayerUI && other) noexcept = delete;

	void SetBoundPlayer(Player* pPlayer);

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	static const std::wstring m_BombIncreaseSprite;
	static const std::wstring m_RadiusIncreaseSprite;
	static const std::wstring m_MovementSpeedSprite;

	const bool m_AlignLeft{};
	const bool m_AlignDown{};
	const XMFLOAT2 m_Pos{};
	std::map<std::wstring, SpriteList*> m_pDisplayedPickups{};

	Player* m_pBoundPlayer{};
	PlayerPickupManager* m_pBoundPickupManager{};

	const PlayerPickupManager::PickupLimits GetDisplayedCounts() const;

	void UpdateDisplayedPickups();
	void UpdateDisplayedPickupsOfType(const std::wstring& sprite, int targetCount);
};


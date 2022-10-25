#pragma once
#include "..\OverlordEngine\Scenegraph\GameScene.h"
#include "Components/TileGridMap.h"
#include "Prefabs/Game/Player/Player.h"
#include "Materials/Post/PostPixelate.h"

struct UISpawnInfo
{
	XMFLOAT2 pos{};
	bool alignDown{};
	bool alignLeft{};
};

class BombermanLevelScene : public GameScene
{
public:
	BombermanLevelScene() :GameScene(L"BombermanLevelScene") {}
	~BombermanLevelScene() override = default;
	BombermanLevelScene(const BombermanLevelScene & other) = delete;
	BombermanLevelScene(BombermanLevelScene && other) noexcept = delete;
	BombermanLevelScene& operator=(const BombermanLevelScene & other) = delete;
	BombermanLevelScene& operator=(BombermanLevelScene && other) noexcept = delete;

protected:
	void Initialize() override;
	void OnSceneActivated() override;

private:
	static std::vector<UISpawnInfo> m_PlayerUILocations;
	static std::vector<XMINT2> m_PlayerSpawns;
	static std::vector<CharacterInputComponent::InputDesc> m_PlayerInputs;

	enum InputIds
	{
		P1_MoveLeft,
		P1_MoveRight,
		P1_MoveUp,
		P1_MoveDown,
		P1_PlaceBomb,

		P2_MoveLeft,
		P2_MoveRight,
		P2_MoveUp,
		P2_MoveDown,
		P2_PlaceBomb,

		P3_MoveLeft,
		P3_MoveRight,
		P3_MoveUp,
		P3_MoveDown,
		P3_PlaceBomb,

		P4_MoveLeft,
		P4_MoveRight,
		P4_MoveUp,
		P4_MoveDown,
		P4_PlaceBomb
	};

	GameObject* m_pTileGridMap{};

	std::vector<Player*> m_pPlayers{};

	PostPixelate* m_pPixelisation{};
};


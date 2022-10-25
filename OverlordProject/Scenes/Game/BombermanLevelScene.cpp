#include "stdafx.h"
#include "BombermanLevelScene.h"
#include "Prefabs/Game/Managers/SpawnManager.h"
#include "Prefabs/Game/UI/PlayerUI.h"
#include "Prefabs/Game/UI/TimerUI.h"
#include "Prefabs/Game/Managers/GameManager.h"
#include "Prefabs/Game/Decoration/BackgroundTile.h"


std::vector<UISpawnInfo> BombermanLevelScene::m_PlayerUILocations{};
std::vector<XMINT2> BombermanLevelScene::m_PlayerSpawns{};
std::vector<CharacterInputComponent::InputDesc>  BombermanLevelScene::m_PlayerInputs
{
	CharacterInputComponent::InputDesc
	{
		P1_MoveLeft,
		P1_MoveRight,
		P1_MoveUp,
		P1_MoveDown,
		P1_PlaceBomb,
		'A',
		'D',
		'W',
		'S',
		'E',
	},
	CharacterInputComponent::InputDesc
	{
		P2_MoveLeft,
		P2_MoveRight,
		P2_MoveUp,
		P2_MoveDown,
		P2_PlaceBomb,
		GamepadIndex::playerOne,
		XINPUT_GAMEPAD_DPAD_LEFT,
		XINPUT_GAMEPAD_DPAD_RIGHT,
		XINPUT_GAMEPAD_DPAD_UP,
		XINPUT_GAMEPAD_DPAD_DOWN,
		XINPUT_GAMEPAD_A,
	},
	CharacterInputComponent::InputDesc
	{
		P3_MoveLeft,
		P3_MoveRight,
		P3_MoveUp,
		P3_MoveDown,
		P3_PlaceBomb,
		GamepadIndex::playerTwo,
		XINPUT_GAMEPAD_DPAD_LEFT,
		XINPUT_GAMEPAD_DPAD_RIGHT,
		XINPUT_GAMEPAD_DPAD_UP,
		XINPUT_GAMEPAD_DPAD_DOWN,
		XINPUT_GAMEPAD_A,
	},
	CharacterInputComponent::InputDesc
	{
		P4_MoveLeft,
		P4_MoveRight,
		P4_MoveUp,
		P4_MoveDown,
		P4_PlaceBomb,
		GamepadIndex::playerThree,
		XINPUT_GAMEPAD_DPAD_LEFT,
		XINPUT_GAMEPAD_DPAD_RIGHT,
		XINPUT_GAMEPAD_DPAD_UP,
		XINPUT_GAMEPAD_DPAD_DOWN,
		XINPUT_GAMEPAD_A,
	},
};

void BombermanLevelScene::Initialize()
{
	// Disable debug draws
	GetSceneSettings().drawGrid = false;
	GetSceneSettings().drawPhysXDebug = false;
#if NDEBUG
	GetSceneSettings().showInfoOverlay = false;
#endif
	// Camera
	{
		FixedCamera* pFixedCam = new FixedCamera();
		AddChild(pFixedCam);
		SetActiveCamera(pFixedCam->GetComponent<CameraComponent>());

		CameraComponent* pActiveCam = GetSceneContext().pCamera;
		pActiveCam->GetTransform()->Translate(0, 20, 0);
		pActiveCam->GetTransform()->Rotate(90, 0, 0);
	}

	// Lights
	m_SceneContext.pLights->SetDirectionalLight({ -95.6139526f,66.1346436f,-41.1850471f }, { 0.740129888f, -0.597205281f, 0.309117377f });

	// background
	BackgroundTile* pBackground{ new BackgroundTile(L"Textures/planks.jpg")};
	pBackground->GetTransform()->Translate(0, -1.f, 0);
	pBackground->GetTransform()->Scale(3.2f);
	AddChild(pBackground);

	// Level
	m_pTileGridMap = new GameObject();
	AddChild(m_pTileGridMap);

	TileGridMap* pMap = m_pTileGridMap->AddComponent(new TileGridMap(15, 13));

	// Add Player Statics
	{
		const XMINT2 mapSize = pMap->GetMapSize();
		m_PlayerSpawns.push_back(XMINT2{ 1, 1 });
		m_PlayerSpawns.push_back(XMINT2{ mapSize.x - 2, mapSize.y - 2 });
		m_PlayerSpawns.push_back(XMINT2{ mapSize.x - 2, 1 });
		m_PlayerSpawns.push_back(XMINT2{ 1, mapSize.y - 2 });

		const XMFLOAT2 window{ GetSceneContext().windowWidth, GetSceneContext().windowHeight };

		//const float step = static_cast<float>(PlayerUI::m_SpriteStep);
		const float margin = static_cast<float>(PlayerUI::m_SpriteStep);
		m_PlayerUILocations.push_back(UISpawnInfo{ XMFLOAT2{ margin, window.y - margin }, false, true}); // bottom left
		m_PlayerUILocations.push_back(UISpawnInfo{ XMFLOAT2{ window.x - margin, margin }, true, false }); // top right
		m_PlayerUILocations.push_back(UISpawnInfo{ XMFLOAT2{ margin, margin }, true, true }); // top left
		m_PlayerUILocations.push_back(UISpawnInfo{ XMFLOAT2{ window.x - margin, window.y - margin }, false, false }); // bottom right
	}


	// Add SpawnManager after level is setup so that during spawning no pickups get spawned
	SpawnManager* pSpawnManager = new SpawnManager(0.2f); // 20% chance
	AddChild(pSpawnManager);

	m_pPixelisation = MaterialManager::Get()->CreateMaterial<PostPixelate>();
	AddPostProcessingEffect(m_pPixelisation);
}
void BombermanLevelScene::OnSceneActivated()
{
	// Spawn players
	size_t amountOfPlayers = 1; // keyboard is always connected

	if (GetSceneContext().pInput->IsGamepadConnected(GamepadIndex::playerOne))
		amountOfPlayers++;
	if (GetSceneContext().pInput->IsGamepadConnected(GamepadIndex::playerTwo))
		amountOfPlayers++;
	if (GetSceneContext().pInput->IsGamepadConnected(GamepadIndex::playerThree))
		amountOfPlayers++;

	for (size_t i = 0; i < amountOfPlayers; i++)
	{
		const CharacterInputComponent::InputDesc& input = m_PlayerInputs[i];
		const XMINT2& spawn = m_PlayerSpawns[i];

		Player* player = new Player(spawn, input);
		player->SetPlayerNumber(static_cast<int>(i) + 1);
		m_pPlayers.push_back(player);
		AddChild(player);

		PlayerUI* pPlayerUI = new PlayerUI(player, m_PlayerUILocations[i].pos, m_PlayerUILocations[i].alignDown, m_PlayerUILocations[i].alignLeft);
		AddChild(pPlayerUI);
	}

	GameManager* pGameManager{ new GameManager(m_pPlayers, 120.f)};
	AddChild(pGameManager);

	TimerUI* pTimer = new TimerUI(pGameManager);
	AddChild(pTimer);
}

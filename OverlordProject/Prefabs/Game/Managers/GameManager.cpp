#include "stdafx.h"
#include "GameManager.h"
#include "Prefabs/Game/Player/Player.h"
#include "Prefabs/Game/UI/Screens/GameEndScreen.h"

const std::wstring GameManager::m_TagName{L"GameManager"};

GameManager::GameManager(const std::vector<Player*>& pPlayers, float roundTime)
	: GameObject{}
	, m_pPlayers{pPlayers}
	, m_StartPlayerCount{static_cast<int>(pPlayers.size())}
	, m_RemainingRoundTime{roundTime}
{
}

void GameManager::OnPlayerDied(Player* pPlayer)
{
	const auto playerItr = std::find(m_pPlayers.begin(), m_pPlayers.end(), pPlayer);
	if (playerItr != m_pPlayers.end())
		m_pPlayers.erase(playerItr);
}

float GameManager::GetRemainingRoundTime() const
{
	return m_RemainingRoundTime;
}

void GameManager::Initialize(const SceneContext&)
{
	SetTag(m_TagName);
}

void GameManager::Update(const SceneContext& sceneContext)
{
	if (m_HasGameEnded)
		return;

	if (m_pPlayers.size() == 1 && m_StartPlayerCount != 1)
		GameEnd();
	else if (m_pPlayers.size() == 0)
		GameEnd();
	else if (m_RemainingRoundTime <= 0.0f)
		GameEnd();

	m_RemainingRoundTime -= sceneContext.pGameTime->GetElapsed();
}

void GameManager::GameEnd()
{
	Player* pWinner{};
	if (m_pPlayers.size() == 1)
		pWinner = m_pPlayers[0];

	GameEndScreen* EndScreen = new GameEndScreen(pWinner);
	GetScene()->AddChild(EndScreen);

	m_HasGameEnded = true;
}

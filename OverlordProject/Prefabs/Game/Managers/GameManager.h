#pragma once
#include "..\OverlordEngine\Scenegraph\GameObject.h"

class Player;

class GameManager : public GameObject
{
public:
	static const std::wstring m_TagName;

	GameManager(const std::vector<Player*>& pPlayers, float roundTime);
	~GameManager() override = default;
	GameManager(const GameManager& other) = delete;
	GameManager(GameManager&& other) noexcept = delete;
	GameManager& operator=(const GameManager& other) = delete;
	GameManager& operator=(GameManager&& other) noexcept = delete;

	void OnPlayerDied(Player* pPlayer);
	float GetRemainingRoundTime() const;

protected:
	void Initialize(const SceneContext&) override;
	void Update(const SceneContext& sceneContext) override;

private:
	const int m_StartPlayerCount{};
	std::vector<Player*> m_pPlayers{};
	float m_RemainingRoundTime{};
	bool m_HasGameEnded{false};

	void GameEnd();
};


#pragma once
#include "../Engine/GameObject.h"

class EnemyBoss;
class Player;

class SceneManager;


class SelectBox;

enum class RetryMenu
{
	Retry,
	GameOver
};

class DebugScene : public GameObject
{
public:

	DebugScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;


	void BattleRetry();

private:

	EnemyBoss* pBoss;
	Player* pPlayer;
	int timer;

	SceneManager* pManager;


	SelectBox* pBox;
	RetryMenu nowMenu;
};
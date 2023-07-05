#pragma once
#include "../Engine/GameObject.h"

class EnemyBoss;
class Player;

const int ENEMY_COUNT = 3;

class DebugScene : public GameObject
{
public:

	DebugScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	EnemyBoss* pBoss;
	Player* pPlayer;
	int timer;
};
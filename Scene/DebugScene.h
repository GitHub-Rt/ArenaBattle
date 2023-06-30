#pragma once
#include "../Engine/GameObject.h"

class EnemyBoss;

const int ENEMY_COUNT = 5;

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
	int timer;
};
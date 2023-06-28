#pragma once
#include "../Engine/GameObject.h"

class Enemy;

const int ENEMY_COUNT = 1;

class DebugScene : public GameObject
{
public:

	DebugScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	Enemy* pEnemy[ENEMY_COUNT];
	int timer;
};
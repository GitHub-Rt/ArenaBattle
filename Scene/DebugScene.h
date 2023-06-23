#pragma once
#include "../Engine/GameObject.h"

class Enemy;

// ’è”éŒ¾
const int ENEMY_COUNT = 1;	// “G‘”

class DebugScene : public GameObject
{
public:

	DebugScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SetEnemyPointer(Enemy* enemy[])
	{
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			enemy[i] = pEnemy[i];
		}
	}

private:	

	int enemyCount;
	Enemy* pEnemy[ENEMY_COUNT];
};
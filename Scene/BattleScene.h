#pragma once
#include "../Engine/GameObject.h"

class SceneManager;
class EnemyBoss;
class Player;


class BattleScene : public GameObject
{
public:

	BattleScene(GameObject* parent);
	~BattleScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	SceneManager* pManager;
	EnemyBoss* pBoss;
	Player* pPlayer;

};


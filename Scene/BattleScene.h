#pragma once
#include "../Engine/GameObject.h"

class SceneManager;
class GameSound;
class EnemyBoss;
class Player;

class SelectBox;

enum class RetryMenu
{
	Retry,
	GameOver
};

class BattleScene : public GameObject
{
public:

	BattleScene(GameObject* parent);
	~BattleScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	// ボスの第二形態に入った時に音楽を変える関数
	void ChangeBossSound();

	// リトライ回りの関数
	void BattleRetry();
	void PoseProcess();

private:

	SceneManager* pManager;
	GameSound* pSound;
	EnemyBoss* pBoss;
	Player* pPlayer;

	SelectBox* pBox;
	RetryMenu nowMenu;
	bool isRetryProcess;

};


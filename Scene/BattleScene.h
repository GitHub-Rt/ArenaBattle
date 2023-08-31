#pragma once
#include "../Engine/GameObject.h"

class SceneManager;
class GameSound;
class EnemyBoss;
class Player;

class SelectBox;
class PauseImage;

enum class RetryMenu
{
	Retry,
	GameOver
};

enum class Menu
{
	BackGame,
	ToStart
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

	// リトライ、ポーズ回りの関数
	void BattleRetry();
	void BackBattle();
	void PoseProcess();

private:

	SceneManager* pManager;
	GameSound* pSound;
	EnemyBoss* pBoss;
	Player* pPlayer;

	SelectBox* pBox;
	PauseImage* pPause;
	RetryMenu nowRetryMenu;
	Menu nowMenu;
	bool isRetryProcess;
	bool isPauseProcess;

};


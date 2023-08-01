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

	// �{�X�̑��`�Ԃɓ��������ɉ��y��ς���֐�
	void ChangeBossSound();

	// ���g���C���̊֐�
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


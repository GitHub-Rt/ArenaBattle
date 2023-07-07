#pragma once
#include "AttackModelBase.h"

class EnemyBoss;
class Player;

class EnemyBossWaves : public AttackModelBase
{
public:
	EnemyBossWaves(GameObject* parent);
	~EnemyBossWaves();
	void Initialize() override;
	void AttackModelUpdate() override;

	// �v���C���[�Ƃ̓����蔻��(�������Ă�����true)
	bool IsCollisionToPlayer();

private:

	EnemyBoss* pBoss;
	Player* pPlayer;
	int scalingTimer;	// �g�厞��
	float inside;		// �����̓����蔻��p
	float outside;		// �O���̓����蔻��p


};


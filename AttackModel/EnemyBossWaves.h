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

	void SetStartPos(XMFLOAT3 pos) { transform_.position_ = pos; }

	// �v���C���[�Ƃ̓����蔻��(�������Ă�����true)
	bool IsCollisionToPlayer();

private:

	EnemyBoss* pBoss;
	Player* pPlayer;
	int scalingTimer;	// �g�厞��

};


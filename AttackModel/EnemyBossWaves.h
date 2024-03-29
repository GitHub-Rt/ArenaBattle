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

	// プレイヤーとの当たり判定(当たっていたらtrue)
	bool IsCollisionToPlayer();

private:

	EnemyBoss* pBoss;
	Player* pPlayer;
	int scalingTimer;	// 拡大時間

};


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

	// プレイヤーとの当たり判定(当たっていたらtrue)
	bool IsCollisionToPlayer();

private:

	EnemyBoss* pBoss;
	Player* pPlayer;
	int scalingTimer;	// 拡大時間
	float inside;		// 内側の当たり判定用
	float outside;		// 外側の当たり判定用


};


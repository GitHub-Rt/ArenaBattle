#pragma once
#include "AttackModelBase.h"

class EnemyBossSpecialArea : public AttackModelBase
{
public:
	EnemyBossSpecialArea(GameObject* parent);
	~EnemyBossSpecialArea();
	void Initialize() override;
	void AttackModelUpdate() override;

private:
	int scaleTimer;	// 拡縮タイマー
};


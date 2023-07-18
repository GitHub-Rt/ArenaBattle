#pragma once
#include "AttackModelBase.h"

class EnemyBoss;

class EnemyBossJumpArea : public AttackModelBase
{
public:
	EnemyBossJumpArea(GameObject* parent);
	~EnemyBossJumpArea();
	void Initialize() override;
	void AttackModelUpdate() override;
	void Draw() override;

	// 可視化させるための準備
	void SetArea(XMFLOAT3 pos);
	

private:
	EnemyBoss* pBoss;
	Transform moveArea;
};


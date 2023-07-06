#pragma once
#include "AttackModelBase.h"

class EnemyBoss;

class EnemyBossBullet : public AttackModelBase
{
public:
	EnemyBossBullet(GameObject* parent);
	~EnemyBossBullet();
	void Initialize() override;
	void AttackModelUpdate() override;
	void OnCollision(GameObject* pTarget, Collider* nowCollider) override;

	void SetMoveDirection(XMFLOAT3 dir){ travelingDirection = dir; }

private:
	EnemyBoss* pBoss;
	XMFLOAT3 travelingDirection;	// êiçsï˚å¸
	XMVECTOR vMove;
};


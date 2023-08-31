#include "EnemyBossBullet.h"
#include "../Character/EnemyBoss.h"

// ’è”éŒ¾
const XMFLOAT3 HIT_TEST_RANGE = XMFLOAT3(0, 3.4f, 0);
const float HIT_TEST_RADIUS = 3.0f;

EnemyBossBullet::EnemyBossBullet(GameObject* parent)
	: AttackModelBase(parent, "EnemyBossBullet")
{
	pBoss = nullptr;
	travelingDirection = { 0,0,0 };
	vMove = { 0,0,0,0 };
}

EnemyBossBullet::~EnemyBossBullet()
{

}

void EnemyBossBullet::Initialize()
{
	AttackModelLoad("enemyBossBullet.fbx");
	AttackModelAddSphereCollider(HIT_TEST_RADIUS, HIT_TEST_RANGE);

	pBoss = (EnemyBoss*)FindObject("EnemyBoss");

}

void EnemyBossBullet::AttackModelUpdate()
{
	const float BULLET_MOVING = 0.005f;

	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	travelingDirection.y = 0;
	vMove = XMLoadFloat3(&travelingDirection);


	// ˆÚ“®
	XMStoreFloat3(&transform_.position_, vPos + vMove);

	if (IsMoveLimit(transform_.position_))
	{
		KillMe();
	}
}

void EnemyBossBullet::OnCollision(GameObject* pTarget, Collider* nowCollider)
{
	if (pTarget->GetObjectName() == "Player")
	{
		pBoss->AttackModelDamageToPlayer(BossAttackModelHandle::Bullet, vMove);
		KillMe();
	}
}
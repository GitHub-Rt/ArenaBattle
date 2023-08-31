#include "EnemyBossWaves.h"

#include "../Character/EnemyBoss.h"
#include "../Character/Player.h"

EnemyBossWaves::EnemyBossWaves(GameObject* parent)
	: AttackModelBase(parent, "EnemyBossWaves")
{
	pBoss = nullptr;
	pPlayer = nullptr;
	scalingTimer = 0;
}

EnemyBossWaves::~EnemyBossWaves()
{

}

void EnemyBossWaves::Initialize()
{
	AttackModelLoad("enemyBossRing.fbx");

	pBoss = (EnemyBoss*)FindObject("EnemyBoss");
	pPlayer = (Player*)FindObject("Player");
}

void EnemyBossWaves::AttackModelUpdate()
{
	const int MAX_SCALING_TIME = 50;				// 拡大最大時間
	const float SCALING_STEP = 0.096f;				// 拡大増加率

	// 最大時間内ならモデルを拡大、時間外なら消す
	if (scalingTimer < MAX_SCALING_TIME)
	{
		scalingTimer++;
		
		transform_.scale_.z += SCALING_STEP;
		transform_.scale_.x += SCALING_STEP;
	}
	else
	{
		scalingTimer = 0;
		KillMe();
	}

	// プレイヤーとの当たり判定
	if (IsCollisionToPlayer())
	{
		// ダメージモーションベクトルの作成
		XMFLOAT3 center = XMFLOAT3(0, 0, 0);
		XMFLOAT3 pos = pPlayer->GetPosition();
		XMVECTOR vDirection = XMLoadFloat3(&pos) - XMLoadFloat3(&center);

		pBoss->AttackModelDamageToPlayer(BossAttackModelHandle::Wave, vDirection);
	}
}

bool EnemyBossWaves::IsCollisionToPlayer()
{
	pPlayer = (Player*)FindObject("Player");

	XMFLOAT3 playerPos = pPlayer->GetPosition();
	if (IsObjectUnder(playerPos, GetAttackModelHandle()) && pPlayer->IsStateSet(CharacterState::Jumping) == false)
	{
		return true;
	}

	return false;

}
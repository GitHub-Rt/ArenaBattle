#include "EnemyBossWaves.h"

#include "../Character/EnemyBoss.h"
#include "../Character/Player.h"

// 定数宣言
const float FIRST_RADIUS = 9.0f;	// 初期値の半径
const FLOAT WAVES_LENGTH = 1.0f;    // 波状攻撃のモデルの長さ
const FLOAT CIRCLE_RANGE = 60.0f;   // 移動可能範囲の半径  

EnemyBossWaves::EnemyBossWaves(GameObject* parent)
	: AttackModelBase(parent, "EnemyBossWaves")
{
	pBoss = nullptr;
	pPlayer = nullptr;
	scalingTimer = 0;
	inside = 0;
	outside = 0;
}

EnemyBossWaves::~EnemyBossWaves()
{

}

void EnemyBossWaves::Initialize()
{
	AttackModelLoad("enemyBossRing.fbx");

	pBoss = (EnemyBoss*)FindObject("EnemyBoss");
	pPlayer = (Player*)FindObject("Player");

	// 当たり判定変数の初期化
	inside = FIRST_RADIUS;
	outside = CIRCLE_RANGE - (FIRST_RADIUS + WAVES_LENGTH);
}

void EnemyBossWaves::AttackModelUpdate()
{
	const int MAX_SCALING_TIME = 45;				// 拡大最大時間
	const float SCALING_STEP = 0.096f;				// 拡大増加率
	const float SCALING_STEP_SECOND = 0.049f;		// 拡大増加率(第二形態)
	const float HIT_TEST_STEP = 0.91f;				// 当たり判定増減率

	// 最大時間内ならモデルを拡大、時間外なら消す
	if (scalingTimer < MAX_SCALING_TIME)
	{
		scalingTimer++;

		//// 形態別に拡大する
		//if (pBoss->GetAIState() == BossAIState::Caution)
		//{
		//	// 第二形態のモデルの拡大
		//	transform_.scale_.x += SCALING_STEP_SECOND;
		//	transform_.scale_.z += SCALING_STEP_SECOND;
		//}
		//else
		//{
		//	// 第一形態のモデルの拡大
		//	transform_.scale_.x += SCALING_STEP;
		//	transform_.scale_.z += SCALING_STEP;
		//}
		
		transform_.scale_.z += SCALING_STEP;
		transform_.scale_.x += SCALING_STEP;

		// 当たり判定変数更新
		inside += HIT_TEST_STEP;
		outside -= HIT_TEST_STEP;
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

	// プレイヤーのポジションとの長さを調べる
	XMFLOAT3 center = pBoss->GetPosition();
	XMFLOAT3 targetPos = pPlayer->GetPosition();

	XMVECTOR vCenter = XMLoadFloat3(&center);
	XMVECTOR vTarget = XMLoadFloat3(&targetPos);

	XMVECTOR vDirection = vCenter - vTarget;
	vDirection = XMVector3Length(vDirection);

	float length = XMVectorGetX(vDirection);
	length -= FIRST_RADIUS;


	// プレイヤーとの当たり判定
	// 内側にいるかどうか
	if (inside < length)
	{
		return false;
	}
	else
	{
		length -= inside;

		// モデル上にいて、プレイヤーの状態がジャンプではないかどうか
		if (length <= WAVES_LENGTH && pPlayer->IsStateSet(CharacterState::Jumping) == false )
		{
			return true;
		}
	}

	return false;
}
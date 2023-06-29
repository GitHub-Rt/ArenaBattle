#include "Enemy.h"

#include "Player.h"
#include "Robot.h"

#include "../Manager/EnemyManager.h"

// 定数宣言
const XMFLOAT3 HIT_TEST_RANGE = { 5, 8, 5 };	// 当たり判定枠
const float JUMP_FIRST_SPEED = 1.6f;			// ジャンプの初速度
const XMFLOAT3 GaugeScale = XMFLOAT3(0.3f, 0.7f, 0);


Enemy::Enemy(GameObject* parent)
	:EnemyBase(parent, "Enemy")
{
	ATTACK_START_RANGE = 0;
	ATTACK_TIME = 0;

	hp = 0;

	vPrevPos = { 0,0,0,0 };

	vAttackMove = { 0,0,0,0 };
	attackTimer = 0;

	beforeJumpY = 0;
	jumpSpeed = 0;
	isJumpSummit = false;
	isStartingAttackMoving = false;

	isHittingPlayer = false;
}

Enemy::~Enemy()
{

}

void Enemy::SetData()
{
	ATTACK_START_RANGE = GetInternalData(CharacterID::NormalEnemy, (int)EnemyData::AttackStartRange);
	ATTACK_TIME = GetInternalData(CharacterID::NormalEnemy, (int)EnemyData::AttackTime);
	DAMAGE_TIME = GetInternalData(CharacterID::NormalEnemy, (int)EnemyData::DamageTimer);
}

void Enemy::Initialize()
{
	SetData();
	SetParameter(CharacterID::NormalEnemy);

	CharacterModelLoad("enemy.fbx");
	hModel = GetCharacterModelHandle();
	CharacterAddCollider(HIT_TEST_RANGE);

	// 変数の初期化
	{
		transform_.position_.x = (float)(rand() % 100 - 50);
		transform_.position_.z = 15;

		hp = GetParameterValue(CharacterID::NormalEnemy, CharacterStatus::HP);
		jumpSpeed = JUMP_FIRST_SPEED;

		transform_.position_.y -= PositionAdjustment(transform_.position_);
	}
}

void Enemy::Draw()
{
	if (IsStateSet(CharacterState::Damaged))
	{
		ChangeDamageColor();	// モデルの色を赤に変更させる
		CharacterDraw(hModel);
	}
	else
	{
		ChangeDamageColor(false);
		CharacterDraw(hModel);
	}
}

void Enemy::EnemyRelease()
{

}

void Enemy::EnemyUpdate()
{
	if (IsStateSet(CharacterState::Moving))
	{
		transform_.position_.y -= PositionAdjustment(transform_.position_);
	}

	CharacterCheckHP();
}

void Enemy::CharacterIdleAction()
{
	ChangeState(CharacterState::Moving);
}

void Enemy::CharacterMove()
{
	const float MOVING_DISTANCE = 0.125f;	// 移動量

	Player* pPlayer = (Player*)FindObject("Player");
	XMFLOAT3 playerPosition = pPlayer->GetPosition();

	vPrevPos = XMLoadFloat3(&transform_.position_);
	XMVECTOR vMove = XMLoadFloat3(&playerPosition) - vPrevPos;

	ModelRotate(vMove);

	float length = XMVectorGetX(XMVector3Length(vMove));

	// Enemyの攻撃開始範囲内にPlayerがいたら、攻撃状態に移行する
	if (length <= ATTACK_START_RANGE)
	{

		XMStoreFloat3(&transform_.position_, vPrevPos);

		vAttackMove = XMVector3Normalize(vMove);

		// 移動状態から攻撃状態に移行
		ClearState(CharacterState::Moving);
		ChangeState(CharacterState::Attacking);
		beforeJumpY = transform_.position_.y;
	}
	else
	{
		vMove = XMVector3Normalize(vMove) * MOVING_DISTANCE;

		XMFLOAT3 nextPos = { 0,0,0 };
		XMStoreFloat3(&nextPos, vMove);

		nextPos.x += transform_.position_.x;
		nextPos.z += transform_.position_.z;

		if (IsMoveLimit(nextPos))
		{
			XMStoreFloat3(&transform_.position_, vPrevPos);
		}
		else
		{
			transform_.position_.x = nextPos.x;
			transform_.position_.z = nextPos.z;
		}
	}
}

void Enemy::ModelRotate(XMVECTOR vMove)
{
	XMVECTOR vNext = vMove;
	XMVECTOR vFront = { 0,0,-1,0 };

	vNext = XMVector3Normalize(vNext);
	vFront = XMVector3Normalize(vFront);

	XMVECTOR dot = XMVector3Dot(vNext, vFront);
	float angle = acos(XMVectorGetX(dot));

	XMVECTOR vCross = XMVector3Cross(vNext, vFront);
	float cross = XMVectorGetY(vCross);
	if (cross > 0)
	{
		angle *= -1;
	}

	transform_.rotate_.y = (float)angle * DEGREES_180 / M_PI;
}

void Enemy::CharacterAttack()
{
	if (isStartingAttackMoving)
	{
		const float VECTOR_LENGTH_ATTACK = 0.65f;	// 攻撃時のベクトルの長さ

		XMVECTOR vMove = vAttackMove * VECTOR_LENGTH_ATTACK;

		XMFLOAT3 motionPos = { 0,0,0 };
		XMStoreFloat3(&motionPos, vMove);

		motionPos.x += transform_.position_.x;
		motionPos.z += transform_.position_.z;

		if (attackTimer <= ATTACK_TIME)
		{
			attackTimer++;
			if (IsMoveLimit(motionPos) == false)
			{
				vPrevPos = XMLoadFloat3(&transform_.position_);

				transform_.position_.x = motionPos.x;
				transform_.position_.z = motionPos.z;
			}
		}
		else
		{
			attackTimer = 0;
			isStartingAttackMoving = false;
			ClearState(CharacterState::Attacking);
			ChangeState(CharacterState::Moving);
		}
	}
	else
	{
		// 攻撃開始として移動する前に小ジャンプをして開始をわかりやすくする
		SmallJump();
	}
	
}

void Enemy::SmallJump()
{
	const float LOWEST_JUMP_VELOCITY_CHANGE_QUANTITY = 0.6f;	// 最低ジャンプ速度変化量
	const float JUMP_GRAVTY_DEGREES = 0.85f;					// ジャンプ重力度
	const float JUMP_DESCENDING_SPEED = 1.09f;					// ジャンプ降下速度

	if (jumpSpeed > LOWEST_JUMP_VELOCITY_CHANGE_QUANTITY && isJumpSummit == false)
	{// 上昇中の処理
		transform_.position_.y += jumpSpeed;
		jumpSpeed *= JUMP_GRAVTY_DEGREES;
	}
	else if (beforeJumpY < transform_.position_.y)
	{// 降下中の処理
		isJumpSummit = true;
		transform_.position_.y -= jumpSpeed;
		jumpSpeed *= JUMP_DESCENDING_SPEED;
	}
	else
	{// ジャンプ終了
		transform_.position_.y = beforeJumpY;
		jumpSpeed = JUMP_FIRST_SPEED;
		isJumpSummit = false;
		isStartingAttackMoving = true;
	}
}

void Enemy::CharacterTakeDamage(float damage)
{
	DamageStage nowStage = GetDamageState();

	switch (nowStage)
	{
	case DamageStage::NoDamage:
		ClearState(CharacterState::Damaged);
		break;
	case DamageStage::DamageStart:
		// 変数の更新
		hp -= damage;
		isHittingPlayer = false;
#ifdef _DEBUG
		isDamage = true;
#endif
		SetDamageStage(DamageStage::TakeDamage);
		break;
	case DamageStage::TakeDamage:
		DamageMotion();
		break;
	case DamageStage::EndDamage:
#ifdef _DEBUG
		isDamage = false;
#endif
		SetDamageStage(DamageStage::NoDamage);
		break;
	default:
		break;
	}

	
}

void Enemy::DamageMotion()
{
	if (damageTimer < DAMAGE_TIME)
	{
		const float NORMAL_DAMAGE_VECTOR = 0.4f;	// 通常攻撃時の移動倍率
		const float HARD_DAMAGE_VECTOR = 0.8f;		// 強攻撃時の移動倍率

		damageTimer++;

		Player* pPlayer = (Player*)FindObject("Player");
		AttackState nowAttack = pPlayer->GetAttackState();

		XMVECTOR vMove = GetFrontVector();

		switch (nowAttack)
		{
		case AttackState::NoAttack:
			break;
		case AttackState::NormalAttack:
			vMove *= NORMAL_DAMAGE_VECTOR;
			break;
		case AttackState::HardAttack:
			vMove *= HARD_DAMAGE_VECTOR;
			break;
		default:
			break;
		}


		if (nowAttack == AttackState::NoAttack)
		{
			Robot* pRobot = (Robot*)FindObject("Robot");
			if (pRobot->IsStateSet(CharacterState::Attacking))
			{
				vMove *= NORMAL_DAMAGE_VECTOR;
			}
		}

		XMFLOAT3 nextPos = { 0, 0, 0 };
		XMStoreFloat3(&nextPos, vMove);

		nextPos.x += transform_.position_.x;
		nextPos.z += transform_.position_.z;

		if (IsMoveLimit(nextPos) == false)
		{
			vPrevPos = XMLoadFloat3(&transform_.position_);

			transform_.position_.x = nextPos.x;
			transform_.position_.z = nextPos.z;
		}
	}
	else
	{
		damageTimer = 0;
		SetDamageStage(DamageStage::EndDamage);
	}
}

void Enemy::CharacterCheckHP()
{
	if (hp < 0)
	{
		EnemyManager::RemoveEnemy(this);
		KillMe();
	}
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		isHittingPlayer = true;

		XMStoreFloat3(&transform_.position_, vPrevPos);

		Player* pPlayer = (Player*)FindObject("Player");

		// プレイヤーが攻撃中ではなく、敵が攻撃中でプレイヤーがダメージを負ってない状態だったらダメージ処理を開始させる
		if (pPlayer->IsStateSet(CharacterState::Attacking) == false)
		{
			if (IsStateSet(CharacterState::Attacking) && pPlayer->GetDamageState() == DamageStage::NoDamage)
			{
				CharacterDamageCalculation(CharacterID::NormalEnemy, CharacterID::Player);
				pPlayer->SetDamageStage(DamageStage::DamageStart);
			}
		}
		else
		{
			// プレイヤーが攻撃中だったらEnemyは攻撃状態をやめる
			ClearState(CharacterState::Attacking);
		}
	}


	if (pTarget->GetObjectName() == "RobotBullet")
	{
		CharacterDamageCalculation(CharacterID::Robot, CharacterID::NormalEnemy);
		SetDamageStage(DamageStage::DamageStart);

		pTarget->KillMe();
	}
}

void Enemy::DrawEffect()
{
}

void Enemy::CharacterStunAction()
{
}

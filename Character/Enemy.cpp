#include "Enemy.h"

#include "Player.h"

// �萔�錾
const XMFLOAT3 HIT_TEST_RANGE = { 5, 8, 5 };	// �����蔻��g
const float JUMP_FIRST_SPEED = 1.6f;			// �W�����v�̏����x

Enemy::Enemy(GameObject* parent)
	:EnemyBase(parent, "Enemy")
{
	vPrevPos = { 0,0,0,0 };

	vAttackMove = { 0,0,0,0 };
	attackTimer = 0;

	beforeJumpY = 0;
	jumpSpeed = 0;
	isJumpSummit = false;
	isStartingAttackMoving = false;
}

Enemy::~Enemy()
{

}

void Enemy::SetData()
{
	ATTACK_START_RANGE = GetInternalData(CharacterID::NormalEnemy, (int)EnemyData::AttackStartRange);
	ATTACK_TIME = GetInternalData(CharacterID::NormalEnemy, (int)EnemyData::AttackTime);
}

void Enemy::Initialize()
{
	SetData();

	CharacterModelLoad("enemy.fbx");
	CharacterAddCollider(HIT_TEST_RANGE);
	
	ChangeState(CharacterState::Moving);

	// �ϐ��̏�����
	{
		jumpSpeed = JUMP_FIRST_SPEED;

		transform_.position_.x = (float)(rand() % 100 - 50);
		transform_.position_.z = 15;
	}
	


}

void Enemy::EnemyRelease()
{

}

void Enemy::CharacterUpdate()
{
	if (IsStateSet(CharacterState::Moving))
	{
		transform_.position_.y -= PositionAdjustment(transform_.position_);
	}


	CharacterCheckHP();
}

void Enemy::CharacterIdleAction()
{

}

void Enemy::CharacterMove()
{
	const float MOVING_DISTANCE = 0.125f;	// �ړ���

	Player* pPlayer = (Player*)FindObject("Player");
	XMFLOAT3 playerPosition = pPlayer->GetPosition();

	vPrevPos = XMLoadFloat3(&transform_.position_);
	XMVECTOR vMove = XMLoadFloat3(&playerPosition) - vPrevPos;

	ModelRotate(vMove);

	float length = XMVectorGetX(XMVector3Length(vMove));

	// Enemy�̍U���J�n�͈͓���Player��������A�U����ԂɈڍs����
	if (length <= ATTACK_START_RANGE)
	{

		XMStoreFloat3(&transform_.position_, vPrevPos);

		vAttackMove = XMVector3Normalize(vMove);

		// �ړ���Ԃ���U����ԂɈڍs
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
		const float VECTOR_LENGTH_ATTACK = 0.9f;	// �U�����̃x�N�g���̒���

		vAttackMove *= VECTOR_LENGTH_ATTACK;

		XMFLOAT3 motionPos = { 0,0,0 };
		XMStoreFloat3(&motionPos, vAttackMove);

		motionPos.x += transform_.position_.x;
		motionPos.z += transform_.position_.z;

		if (attackTimer <= ATTACK_TIME)
		{
			attackTimer++;
			if (IsMoveLimit(motionPos))
			{
				XMStoreFloat3(&motionPos, vPrevPos);
			}
			else
			{
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
		// �U���J�n�Ƃ��Ĉړ�����O�ɏ��W�����v�����ĊJ�n���킩��₷������
		SmallJump();
	}
	
}

void Enemy::SmallJump()
{
	const float LOWEST_JUMP_VELOCITY_CHANGE_QUANTITY = 0.6f;	// �Œ�W�����v���x�ω���
	const float JUMP_GRAVTY_DEGREES = 0.85f;					// �W�����v�d�͓x
	const float JUMP_DESCENDING_SPEED = 1.09f;					// �W�����v�~�����x

	if (jumpSpeed > LOWEST_JUMP_VELOCITY_CHANGE_QUANTITY && isJumpSummit == false)
	{// �㏸���̏���
		transform_.position_.y += jumpSpeed;
		jumpSpeed *= JUMP_GRAVTY_DEGREES;
	}
	else if (beforeJumpY < transform_.position_.y)
	{// �~�����̏���
		isJumpSummit = true;
		transform_.position_.y -= jumpSpeed;
		jumpSpeed *= JUMP_DESCENDING_SPEED;
	}
	else
	{// �W�����v�I��
		transform_.position_.y = beforeJumpY;
		jumpSpeed = JUMP_FIRST_SPEED;
		isJumpSummit = false;
		isStartingAttackMoving = true;
	}
}

void Enemy::CharacterTakeDamage(float damage)
{

}

void Enemy::CharacterCheckHP()
{

}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		XMStoreFloat3(&transform_.position_, vPrevPos);

		if (IsStateSet(CharacterState::Attacking))
		{
			Player* pPlayer = (Player*)FindObject("Player");
			if (pPlayer->GetDamageState() == DamageStage::NoDamage)
			{
				pPlayer->SetDamageStage(DamageStage::DamageStart);
			}
		}


	}

	if (pTarget->GetObjectName() == "RobotBullet")
	{

	}
}

void Enemy::DrawEffect()
{

}

void Enemy::CharacterStunAction()
{

}

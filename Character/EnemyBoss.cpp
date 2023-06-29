#include "EnemyBoss.h"
#include "../UI/EnemyBossGauge.h"

// �萔�錾
const XMFLOAT3 HIT_TEST_RANGE = { 18,10,18 };
const FLOAT ENTRY_FALL_SPEED = 1.6f;

EnemyBoss::EnemyBoss(GameObject* parent)
	: EnemyBase(parent, "EnemyBoss")
{
	pGauge = nullptr;
}

EnemyBoss::~EnemyBoss()
{

}

void EnemyBoss::SetData()
{
	ENTRY_FIRST_POS_Y = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::EntryFirstPosY);
	ATTACK_INTERVAL_TIME = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::AttackIntervalTime);
}

void EnemyBoss::Initialize()
{
	SetData();
	SetParameter(CharacterID::EnemyBoss);

	CharacterModelLoad("enemyBoss.fbx");
	CharacterAddCollider(HIT_TEST_RANGE);

	// �ϐ��̏�����
	{
		// ���n�_��y���W��ݒ�
		ENTRY_POS_Y = transform_.position_.y - PositionAdjustment(transform_.position_);

		transform_.position_.y = ENTRY_FIRST_POS_Y;

		// �e��Y����Ԃ�����
		Leave();		// Update
		Invisible();	// Draw
	}
	

	
}

void EnemyBoss::EnemyRelease()
{

}

void EnemyBoss::EnemyUpdate()
{
	if (IsStateSet(CharacterState::Attacking) == false)
	{
		transform_.position_.y -= PositionAdjustment(transform_.position_);
	}

	CharacterCheckHP();

}

void EnemyBoss::CharacterIdleAction()
{

}

void EnemyBoss::CharacterMove()
{

}

void EnemyBoss::CharacterAttack()
{

}

void EnemyBoss::CharacterTakeDamage(float damage)
{
	DamageStage nowState = GetDamageState();

	switch (nowState)
	{
	case DamageStage::NoDamage:
		ClearState(CharacterState::Damaged);
		break;
	case DamageStage::DamageStart:
		pGauge->Damage(damage);
		hp -= damage;

		ColorChange(1, 0, 0, 0);
		SetDamageStage(DamageStage::TakeDamage);
		break;
	case DamageStage::TakeDamage:
		break;
	case DamageStage::EndDamage:
		RestoreOriginalColor();
		SetDamageStage(DamageStage::NoDamage);
		break;
	default:
		break;
	}
}

void EnemyBoss::CharacterCheckHP()
{

}

void EnemyBoss::DrawEffect()
{

}

void EnemyBoss::CharacterStunAction()
{

}

void EnemyBoss::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "RobotBullet")
	{
		CharacterDamageCalculation(CharacterID::Robot, CharacterID::EnemyBoss);

		pTarget->KillMe();
	}
}

void EnemyBoss::BossEntry()
{
	// �`���������
	Visible();

	ProcessStart();
}

void EnemyBoss::ProcessStart()
{
	pGauge = Instantiate<EnemyBossGauge>(GetParent());


	// �X�V������������
	Enter();
}
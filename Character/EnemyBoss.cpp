#include "EnemyBoss.h"
#include "../UI/EnemyBossGauge.h"

#include "Player.h"

// ’è”éŒ¾
const XMFLOAT3 HIT_TEST_RANGE_OUTSIDE = { 18,18,18 };	//outside‚Ì“–‚½‚è”»’è˜g
const XMFLOAT3 HIT_TEST_RANGE_INSIDE = { 12, 18, 12 };	//inside‚Ì“–‚½‚è”»’è˜g
const FLOAT ENTRY_FALL_SPEED = 1.6f;

EnemyBoss::EnemyBoss(GameObject* parent)
	: EnemyBase(parent, "EnemyBoss")
{
	pPlayer = nullptr;
	pGauge = nullptr;

	bossAttackState = BossAttackState::NoAttack;
}

EnemyBoss::~EnemyBoss()
{

}

void EnemyBoss::SetData()
{
	ENTRY_FIRST_POS_Y = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::EntryFirstPosY);
	ATTACK_INTERVAL_TIME = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::AttackIntervalTime);
	DAMAGE_TIME = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::DamageTime);
}

void EnemyBoss::Initialize()
{
	SetData();
	SetParameter(CharacterID::EnemyBoss);

	CharacterModelLoad("enemyBoss.fbx");
	
	
	CharacterAddCollider(HIT_TEST_RANGE_OUTSIDE);
	CharacterAddCollider(HIT_TEST_RANGE_INSIDE);


	// •Ï”‚Ì‰Šú‰»
	{
		// ’…’n“_‚ÌyÀ•W‚ğİ’è
		ENTRY_POS_Y = transform_.position_.y - PositionAdjustment(transform_.position_);

		transform_.position_.y = ENTRY_FIRST_POS_Y;


		hp = GetParameterValue(CharacterID::EnemyBoss, CharacterStatus::HP);
		

		// ŠeíŠY“–ó‘Ô‚ğ‹‘”Û
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
		SetDamageStage(DamageStage::TakeDamage);
		break;
	case DamageStage::TakeDamage:
		DamageMotion();
		break;
	case DamageStage::EndDamage:
		RestoreOriginalColor();
		SetDamageStage(DamageStage::NoDamage);
		break;
	default:
		break;
	}
}

void EnemyBoss::DamageMotion()
{
	if (damageTimer < DAMAGE_TIME)
	{
		damageTimer++;
		ColorChange(1, 0, 0, 1);
	}
	else
	{
		damageTimer = 0;
		SetDamageStage(DamageStage::EndDamage);
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

void EnemyBoss::OnCollision(GameObject* pTarget, Collider* nowCollider)
{	
	if (pTarget->GetObjectName() == "Player")
	{
		pPlayer = (Player*)FindObject("Player");

		if (IsStateSet(CharacterState::Attacking))
		{
			// UŒ‚”{—¦‚Ìİ’è
			float atackMagnification = 1.0f;
			switch (bossAttackState)
			{
			case BossAttackState::NoAttack:
				break;
			case BossAttackState::SpiralMoveAttack:
				//atackMagnification =
				break;
			case BossAttackState::JumpAttack:
				//atackMagnification =
				break;
			default:
				break;
			}

			CharacterDamageCalculation(CharacterID::EnemyBoss, CharacterID::Player, 0, atackMagnification);
			pPlayer->SetDamageStage(DamageStage::DamageStart);
			pPlayer->SetDamageDirection(-(GetFrontVector()));
		}
		
	}


	if (pTarget->GetObjectName() == "RobotBullet")
	{
		CharacterDamageCalculation(CharacterID::Robot, CharacterID::EnemyBoss);
		SetDamageStage(DamageStage::DamageStart);

		pTarget->KillMe();
	}
}

void EnemyBoss::BossEntry()
{
	// •`‰æ‚ğ‹–‰Â‚·‚é
	Visible();

	ProcessStart();
}

void EnemyBoss::ProcessStart()
{
	pGauge = Instantiate<EnemyBossGauge>(GetParent());

	// XVˆ—‚ğ‹–‰Â‚·‚é
	Enter();
}
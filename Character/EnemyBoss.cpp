#include "EnemyBoss.h"
#include "../UI/EnemyBossGauge.h"

#include "Player.h"
//#include "../AttackModel/"

// ’è”éŒ¾
const XMFLOAT3 HIT_TEST_RANGE_OUTSIDE = { 18,18,18 };	//outside‚Ì“–‚½‚è”»’è˜g
const XMFLOAT3 HIT_TEST_RANGE_INSIDE = { 12, 18, 12 };	//inside‚Ì“–‚½‚è”»’è˜g
const FLOAT ENTRY_FALL_SPEED = 1.6f;

EnemyBoss::EnemyBoss(GameObject* parent)
	: EnemyBase(parent, "EnemyBoss")
{
	pPlayer = nullptr;
	pGauge = nullptr;

	bossAttackState = (unsigned int)BossAttackState::NoAttack;
	bossAIState = BossAIState::Allowance;
	
	attackIntervalTimer = 0;

	hp = 0;

	isWarningStart = false;

	damageTimer = 0;
	totalDamages = 0;
}

EnemyBoss::~EnemyBoss()
{

}

void EnemyBoss::SetData()
{
	ENTRY_FIRST_POS_Y = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::EntryFirstPosY);
	ATTACK_INTERVAL_TIME = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::AttackIntervalTime);
	DAMAGE_TIME = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::DamageTime);
	RATE_FOR_MAX_STRENGTH = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::RateForMaxStrength);
	TOTAL_DAMAGES_UP_AI_LEVEl = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::TotalDamagesUpAILevel);
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
	attackIntervalTimer++;

	// AIƒŒƒxƒ‹‚ÅUŒ‚ŠÔŠuŠÔ‚ğ•Ï“®‚³‚¹‚é
	if (attackIntervalTimer >= ATTACK_INTERVAL_TIME / (int)bossAIState)
	{
		attackIntervalTimer = 0;

		AttackTypeSelection();
		ChangeState(CharacterState::Attacking);
	}

	// Å‘å‘Ì—Í‚É‘Î‚µ‚ÄŒ»İ‘Ì—Í‚ÌŠ„‡‚ªˆê’èˆÈ‰º‚É‚È‚Á‚½‚ç“ÁêUŒ‚‚ğs‚¤
	if (isSpecialAttack == false && hp <= GetParameterValue(CharacterID::EnemyBoss, CharacterStatus::HP) / RATE_FOR_MAX_STRENGTH)
	{
		isSpecialAttack = true;
		attackIntervalTimer = 0;

		// AIó‘Ô‚ğÅ‘åó‘Ô‚É‚·‚é
		bossAIState = BossAIState::Caution;

		// “ÁêUŒ‚‚ğs‚¤
		ChangeAttackState(BossAttackState::SpecialAttack);
		
		ChangeState(CharacterState::Attacking);
	}
}

void EnemyBoss::CharacterMove()
{

}

void EnemyBoss::AttackTypeSelection()
{
	int type = 0;

	switch (bossAIState)
	{
	case BossAIState::Allowance:
		ChangeAttackState(BossAttackState::BulletAttack);
		break;
	case BossAIState::Normal:
		std::srand(unsigned(time(NULL)));
		bossAttackState = (unsigned int)(1 << rand() % 4 + 1);
		break;
	case BossAIState::Caution:
		std::srand(unsigned(time(NULL)));
		type = rand() % 2 + 1;
		if (type == 1)
		{
			ChangeAttackState(BossAttackState::BulletAttack);
			ChangeAttackState(BossAttackState::SpiralMoveAttack);
		}
		else
		{
			ChangeAttackState(BossAttackState::WavesAttack);
			ChangeAttackState(BossAttackState::JumpAttack);
		}
		break;
	default:
		break;
	}
}

void EnemyBoss::CharacterAttack()
{
	for (unsigned int nowState = (unsigned int)BossAttackState::NoAttack; nowState <= (unsigned int)BossAttackState::MaxAttackState; nowState++)
	{
		BossAttackState nowAttack = (BossAttackState)nowState;

		switch (nowAttack)
		{
		case BossAttackState::NoAttack:
			ClearState(CharacterState::Attacking);
			break;
		case BossAttackState::BulletAttack:
			BulletAttackAction();
			break;
		case BossAttackState::SpiralMoveAttack:
			SpiralMoveAttackAction();
			break;
		case BossAttackState::WavesAttack:
			WavesAttackAction();
			break;
		case BossAttackState::JumpAttack:
			JumpAttackAction();
			break;
		case BossAttackState::SpecialAttack:
			SpecialAttackAction();
			break;
		default:
			break;
		}
	}
}

void EnemyBoss::BulletAttackAction()
{

}

void EnemyBoss::SpiralMoveAttackAction()
{

}

void EnemyBoss::WavesAttackAction()
{

}

void EnemyBoss::JumpAttackAction()
{

}

void EnemyBoss::SpecialAttackAction()
{

}

void EnemyBoss::AttackVariableReset(BossAttackState nowState)
{
	switch (nowState)
	{
	case BossAttackState::NoAttack:
		break;
	case BossAttackState::BulletAttack:
		break;
	case BossAttackState::SpiralMoveAttack:
		break;
	case BossAttackState::WavesAttack:
		break;
	case BossAttackState::JumpAttack:
		break;
	case BossAttackState::SpecialAttack:
		break;
	default:
		break;
	}
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
		Damage(damage);
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

void EnemyBoss::Damage(float damage)
{
	pGauge->Damage(damage);
	hp -= damage;
	totalDamages += damage;

	// ˆê’èˆÈãƒ_ƒ[ƒW‚ğ—^‚¦‚½‚çAIƒŒƒxƒ‹‚ğˆê’iŠKã‚°‚é
	if (totalDamages >= TOTAL_DAMAGES_UP_AI_LEVEl)
	{
		bossAIState = BossAIState::Normal;
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
	if (hp < 0)
	{
		//KillMe();
	}
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

			for (unsigned int nowState = (unsigned int)BossAttackState::NoAttack; nowState <= (unsigned int)BossAttackState::MaxAttackState; nowState++)
			{
				BossAttackState nowAttack = (BossAttackState)nowState;

				switch (nowAttack)
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

void EnemyBoss::AttackModelDamageToPlayer(BossAttackModelHandle attackSource)
{
	// UŒ‚”{—¦‚Ìİ’è
	float atackMagnification = 1.0f;

	// ƒ‚ƒfƒ‹ƒnƒ“ƒhƒ‹•Ê‚É”{—¦‚ğİ’è
	switch (attackSource)
	{
	case BossAttackModelHandle::Bullet:
		//atackMagnification =
		break;
	case BossAttackModelHandle::Wave:
		//atackMagnification =
		break;
	default:
		break;
	}

	
	CharacterDamageCalculation(CharacterID::EnemyBoss, CharacterID::Player, 0, atackMagnification);
	pPlayer->SetDamageStage(DamageStage::DamageStart);
	pPlayer->SetDamageDirection(-(GetFrontVector()));
}

bool EnemyBoss::BossEntry()
{
	const float FAIL_SPEED = 0.5f;

	// •`‰æ‚ğ‹–‰Â‚·‚é
	Visible();

	if (isWarningStart == false)
	{
		isWarningStart = true;

		// Warning‚Ì‰æ‘œ‰Šú‰»
	}

	if (transform_.position_.y > ENTRY_POS_Y)
	{
		transform_.position_.y -= FAIL_SPEED;
		return false;
	}
	else
	{
		transform_.position_.y = ENTRY_POS_Y;
		return true;
	}
}

void EnemyBoss::ProcessStart()
{
	pGauge = Instantiate<EnemyBossGauge>(GetParent());

	// XVˆ—‚ğ‹–‰Â‚·‚é
	Enter();
}

void EnemyBoss::ChangeAttackState(BossAttackState nextState)
{
	bossAttackState |= (unsigned int)nextState;

	if (IsAttackState(BossAttackState::NoAttack) && nextState != BossAttackState::NoAttack)
	{
		ClearAttackState(BossAttackState::NoAttack);
	}
}

void EnemyBoss::ClearAttackState(BossAttackState state)
{
	bossAttackState &= ~(unsigned int)state;
	ChangeForNoAttack();
}

void EnemyBoss::ChangeForNoAttack()
{
	bool isTrueAttackState = false;

	for (unsigned int nowState = (unsigned int)BossAttackState::NoAttack; nowState < (unsigned int)BossAttackState::MaxAttackState; nowState++)
	{
		BossAttackState nowAttack = (BossAttackState)nowState;

		if (IsAttackState(nowAttack))
		{
			isTrueAttackState = true;
		}
	}

	if (isTrueAttackState == false)
	{
		ChangeAttackState(BossAttackState::NoAttack);
	}
}

#include "EnemyBoss.h"
#include "../UI/EnemyBossGauge.h"

#include "../Effect/PolyLine.h"
#include "../Effect/Effect.h"

#include "Player.h"
#include "../AttackModel/EnemyBossBullet.h"
#include "../AttackModel/EnemyBossWaves.h"
#include "../AttackModel/EnemyBossJumpArea.h"
#include "../AttackModel/EnemyBossSpecialArea.h"
#include "../UI/Warning.h"
#include "../Scene/BattleScene.h"
#include "../Scene/SceneManager.h"

// �萔�錾
const XMFLOAT3 HIT_TEST_RANGE_OUTSIDE = { 18, 9,18 };	//outside�̓����蔻��g
const XMFLOAT3 HIT_TEST_RANGE_INSIDE = { 12, 16, 12 };	//inside�̓����蔻��g
const FLOAT ENTRY_FALL_SPEED = 1.6f;

EnemyBoss::EnemyBoss(GameObject* parent)
	: EnemyBase(parent, "EnemyBoss")
{
	ENTRY_FIRST_POS_Y = 0;
	ATTACK_INTERVAL_TIME = 0;
	DAMAGE_TIME = 0;
	RATE_FOR_MAX_STRENGTH = 0;
	TOTAL_DAMAGES_UP_AI_LEVEl = 0;
	BULLET_ATK_INTERVAL_TIME = 0;
	BULLET_ATK_MAX_COUNT = 0;
	BULLET_ATK_MAGNIFICATION = 0;
	SPIRAL_MOVE_ATK_MAGNIFICATION = 0;
	WAVES_ATK_MAX_COUNT = 0;
	WAVES_ATK_MAGNIFICATION = 0;
	JUMP_ATK_MAX_COUNT = 0;
	JUMP_ATK_BET_TIMER = 0;
	JUMP_ATK_MAGNIFICATION = 0;
	TIME_UP_TO_SPECIAL_ATTACK = 0;
	SPECIAL_ATK_MAGNIFICATION = 0;

	ENTRY_POS_Y = 0;

	pPlayer = nullptr;
	pEffect = nullptr;
	bossAttackState = (unsigned int)BossAttackState::NoAttack;
	bossAIState = BossAIState::Allowance;
	firstPos = { 0,0,0 };

	attackIntervalTimer = 0;
	jumpSpeed = 0;

	bulletTimer = 0;
	bulletCount = 0;

	pLine = nullptr;
	spiralAngle = 0;
	spiralRadius = 0;
	isEndLine = false;
	isDrawPolyLine = false;
	
	wavesCount = 0;
	wavesJumpTimer = 0;

	pArea = nullptr;
	jumpBetTimer = 0;
	jumpCount = 0;
	landingPosition = { 0,0,0 };
	isPointGetting = false;

	pSpecialArea = nullptr;
	specialTimer = 0;
	isSpecialAttack = false;

	pGauge = nullptr;
	maxHp = 0;
	hp = 0;

	pWarning = nullptr;

	damageTimer = 0;
	totalDamages = 0;

#ifdef _DEBUG

	isSelectAttack = false;
	isImmortality = false;

#endif
}

EnemyBoss::~EnemyBoss()
{
	if (pLine != nullptr)
	{
		pLine->Release();
		SAFE_DELETE(pLine);
	}
}

void EnemyBoss::SetData()
{
	ENTRY_FIRST_POS_Y = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::EntryFirstPosY);
	ATTACK_INTERVAL_TIME = (int)GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::AttackIntervalTime);
	DAMAGE_TIME = (int)GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::DamageTime);
	RATE_FOR_MAX_STRENGTH = (int)GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::RateForMaxStrength);
	TOTAL_DAMAGES_UP_AI_LEVEl = (int)GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::TotalDamagesUpAILevel);
	BULLET_ATK_INTERVAL_TIME = (int)GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::BulletAtkIntervalTime);
	BULLET_ATK_MAX_COUNT = (int)GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::BulletAtkMaxCount);
	BULLET_ATK_MAGNIFICATION = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::BulletAtkMagnification);
	SPIRAL_MOVE_ATK_MAGNIFICATION = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::SpiralMoveAtkMagnification);
	WAVES_ATK_MAX_COUNT = (int)GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::WavesAtkMaxCount);
	WAVES_ATK_MAGNIFICATION = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::WavesAtkMagnification);
	JUMP_ATK_MAX_COUNT = (int)GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::JumpAtkMaxCount);
	JUMP_ATK_BET_TIMER = (int)GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::JumpAtkBetTimer);
	JUMP_ATK_MAGNIFICATION = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::JumpAtkMagnification);
	TIME_UP_TO_SPECIAL_ATTACK = (int)GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::TimeUpToSpecialAttack);
	SPECIAL_ATK_MAGNIFICATION = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::SpecialAtkMagnification);

}

void EnemyBoss::Initialize()
{
	SetData();
	SetParameter(CharacterID::EnemyBoss);

	CharacterModelLoad("enemyBoss.fbx");
	
	CharacterAddCollider(HIT_TEST_RANGE_OUTSIDE);
	CharacterAddCollider(HIT_TEST_RANGE_INSIDE);


	// �ϐ��̏�����
	{
		// ���n�_��y���W��ݒ�
		
		ENTRY_POS_Y = transform_.position_.y;
		firstPos = transform_.position_;
		//firstPos.y -= PositionAdjustment(transform_.position_);
		transform_.position_.y = ENTRY_FIRST_POS_Y;


		hp = (float)GetParameterValue(CharacterID::EnemyBoss, CharacterStatus::HP);
		maxHp = hp;

		pLine = new PolyLine();
		pLine->Load("Effect/tex.png");

		pEffect = new Effect();

		// �e��Y����Ԃ�����
		Leave();		// Update
		Invisible();	// Draw
	}
}

void EnemyBoss::EnemyRelease()
{
	if (pLine != nullptr)
	{
		pLine->Release();
		SAFE_DELETE(pLine);
	}

	if (pEffect != nullptr)
	{
		pEffect->Release();
		SAFE_DELETE(pEffect);
	}
}

void EnemyBoss::EnemyUpdate()
{
	if (IsStateSet(CharacterState::Attacking) == false)
	{
		transform_.position_.y -= PositionAdjustment(transform_.position_);
	}

	if (IsStateSet(CharacterState::Attacking) == false)
	{
		AttackStartTimer();
	}
	
	CharacterCheckHP();
}

void EnemyBoss::CharacterIdleAction()
{
	
}

void EnemyBoss::AttackStartTimer()
{
	attackIntervalTimer++;

	// AI���x���ōU���Ԋu���Ԃ�ϓ�������
	if (attackIntervalTimer >= ATTACK_INTERVAL_TIME / (int)bossAIState)
	{
		attackIntervalTimer = 0;

		AttackTypeSelection();
		ChangeState(CharacterState::Attacking);
	}

	// �ő�̗͂ɑ΂��Č��ݑ̗͂̊��������ȉ��ɂȂ��������U�����s��
	if (isSpecialAttack == false && hp <= maxHp / RATE_FOR_MAX_STRENGTH)
	{
		SecondFormStart();
	}
}

void EnemyBoss::SecondFormStart()
{
#ifdef _DEBUG

	// ����m�F���Ȃ疳������
	if (isSelectAttack)
	{
		return;
	}

#endif


	// ���g���C���ɌĂ΂ꂽ��HP������������
	if (hp == maxHp)
	{
		float reHP = maxHp - (maxHp / RATE_FOR_MAX_STRENGTH);
		Damage(reHP);
	}
	
	
	isSpecialAttack = true;
	attackIntervalTimer = 0;

	// AI��Ԃ��ő��Ԃɂ���
	bossAIState = BossAIState::Caution;

	// ����U�����s��
	ChangeAttackState(BossAttackState::SpecialAttack);

	ChangeState(CharacterState::Attacking);
}

void EnemyBoss::AttackTypeSelection()
{
	int type = 0;

#ifdef _DEBUG

	// ����m�F���Ȃ疳������
	if (isSelectAttack)
	{
		return;
	}
	

#endif

	switch (bossAIState)
	{
	case BossAIState::Allowance:
		ChangeAttackState(BossAttackState::BulletAttack);
		break;
	case BossAIState::Normal:
		std::srand(unsigned(time(NULL)));
		bossAttackState = (unsigned int)(1 << (rand() % 4 + 1));
		break;
	case BossAIState::Caution:
		std::srand(unsigned(time(NULL)));
		type = rand() % 3 + 1;
		if (type == 1)
		{
			ChangeAttackState(BossAttackState::BulletAttack);
		}
		else if(type == 2)
		{
			ChangeAttackState(BossAttackState::SpiralMoveAttack);
		}
		else
		{
			ChangeAttackState(BossAttackState::JumpAttack);	// WavesAttack�������ɍs��
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

		if (IsAttackState(nowAttack))
		{
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
}

void EnemyBoss::BulletAttackAction()
{
	const float BULLET_ATK_ROTATE_ME = 0.5f;
	
	transform_.rotate_.y += BULLET_ATK_ROTATE_ME;
	bulletTimer++;

	if (bulletTimer == BULLET_ATK_INTERVAL_TIME)
	{
		bulletTimer = 0;

		// �O�㍶�E�ɒe���o��
		BulletAttackCal("FRONT");
		BulletAttackCal("BACK");
		BulletAttackCal("RIGHT");
		BulletAttackCal("LEFT");


		bulletCount++;
	}

	// �U�����I���邩�ǂ����̊m�F
	if (bulletCount == BULLET_ATK_MAX_COUNT)
	{
		AttackVariableReset(BossAttackState::BulletAttack);
	}
}

void EnemyBoss::BulletAttackCal(std::string dirName)
{
	const float LENGTH_HALF = 0.5f;	// �ړ��x�N�g���̒�������

	EnemyBossBullet* pBullet = Instantiate<EnemyBossBullet>(GetParent());

	XMFLOAT3 rootPos, tipPos;			// �{�[���|�W�V�����p
	XMFLOAT3 moveDir;					// �i�s����

	rootPos = Model::GetBonePosition(GetCharacterModel(), dirName + "_Root");
	tipPos = Model::GetBonePosition(GetCharacterModel(), dirName + "_Tip");

	XMVECTOR vRoot = XMLoadFloat3(&rootPos);
	XMVECTOR vTip = XMLoadFloat3(&tipPos);

	XMVECTOR vMove = vTip - vRoot;
	if (dirName == "BACK")
	{
		vMove *= -1;	// �������̎��̓x�N�g���̌����𔽓]
	}
	vMove = XMVector3Normalize(vMove);

	vMove *= LENGTH_HALF;

	XMStoreFloat3(&moveDir, vMove);

	pBullet->SetPosition(tipPos);
	pBullet->SetMoveDirection(moveDir);
}

void EnemyBoss::SpiralMoveAttackAction()
{
	const float RADIUS_STEP = 1.7f;				// ���a�̑�����
	const float ANGLE_STEP = 0.05f;				// ��]�p�x�̑�����
	const float MOVING_MAGNIFICATION = 0.05f;	// �ړ��ʔ{��
	
	// �ʒu�ݒ�p�ϐ�
	float nextPosX, nextPosZ;

	if (isEndLine)
	{// �����ɋ��܂�
		spiralAngle -= ANGLE_STEP;
		spiralRadius -= RADIUS_STEP;

		nextPosX = spiralRadius * sin(spiralAngle);
		nextPosZ = spiralRadius * cos(spiralAngle);
	}
	else
	{// �O���ɍL����
		spiralAngle += ANGLE_STEP;
		spiralRadius += RADIUS_STEP;

		nextPosX = spiralRadius * cos(spiralAngle);
		nextPosZ = spiralRadius * sin(spiralAngle);
	}

	// �����ړ�
	transform_.position_.x = nextPosX * MOVING_MAGNIFICATION;
	transform_.position_.z = nextPosZ * MOVING_MAGNIFICATION;

	// PolyLine
	pLine->AddPosition(transform_.position_);
	isDrawPolyLine = true;

	// �[�ɓ��B�������ǂ���
	if (IsMoveLimit(transform_.position_) && isEndLine == false)
	{
		isEndLine = true;
	}

	// �����ʒu���ӂɖ߂��Ă������ǂ���
	if (isEndLine && IsFirstPosAround(transform_.position_))
	{
		transform_.position_.x = firstPos.x;
		transform_.position_.z = firstPos.z;
		AttackVariableReset(BossAttackState::SpiralMoveAttack);
	}

}

void EnemyBoss::WavesAttackAction()
{
	const int WAVES_ATK_BEFORE_TIME = 60;		// �U���O�̎���
	const float WAVES_JUMP_SPEED_STEP = 0.0125f;	// �U���O�̃W�����v�����l

	if (wavesCount < WAVES_ATK_MAX_COUNT)
	{
		// �㏸������
		if (wavesJumpTimer < WAVES_ATK_BEFORE_TIME)
		{
			wavesJumpTimer++;

			
			jumpSpeed += WAVES_JUMP_SPEED_STEP;
			transform_.position_.y += jumpSpeed;
		}
		else
		{

			wavesJumpTimer = 0;
			jumpSpeed = 0;

			// ���ɒ��n
			transform_.position_.y -= PositionAdjustment(transform_.position_);

			// �g��U�����s��
			EnemyBossWaves* pWaves = Instantiate<EnemyBossWaves>(GetParent());
			pWaves->SetStartPos(transform_.position_);
			wavesCount++;
		}
	}
	else
	{
		AttackVariableReset(BossAttackState::WavesAttack);
	}

}

void EnemyBoss::JumpAttackAction()
{
	const float JUMP_ATK_JUMP_STEP = 0.25f;	// �W�����v�U���O�̕ω���(�㏸��)

	if (jumpCount < JUMP_ATK_MAX_COUNT)
	{// �U������


		if (jumpBetTimer < JUMP_ATK_BET_TIMER)
		{// �㏸����
			jumpBetTimer++;

			// ���n�n�_�̏����擾�������ǂ���
			if (isPointGetting == false)
			{
				isPointGetting = true;

				// ���f���ŗ�����ꏊ������������
				pPlayer = (Player*)FindObject("Player");
				landingPosition = pPlayer->GetPosition();
				pArea = Instantiate<EnemyBossJumpArea>(GetParent());
				pArea->SetArea(landingPosition);
			}

			jumpSpeed += JUMP_ATK_JUMP_STEP;
			transform_.position_.y += jumpSpeed;

		}
		else
		{// ���n����
			
			transform_.position_.x = landingPosition.x;
			transform_.position_.y -= PositionAdjustment(transform_.position_);
			transform_.position_.z = landingPosition.z;

			// AI���x�����ő傾������g��U�����s��
			if (bossAIState == BossAIState::Caution && wavesCount == 0)
			{
				// �g��U���J�n
				EnemyBossWaves* pWaves = Instantiate<EnemyBossWaves>(GetParent());
				pWaves->SetStartPos(transform_.position_);
				wavesCount++;
			}

			// �������������f��������
			if (pArea != nullptr)
			{
				pArea->KillMe();
				pArea = nullptr;
			}

			// �W�����v�U����ɏ�����~������(�O��̃J�E���g�̂��ߓ�{�ɂ���)
			if (jumpBetTimer > JUMP_ATK_BET_TIMER * 2)
			{
				// �ϐ����X�V���Ď��̃W�����v�U�����s�킹��
				jumpBetTimer = 0;
				jumpSpeed = 0;
				isPointGetting = false;
				jumpCount++;

				// AI���x�����ő�̎��͔g��U���̕ϐ����X�V����
				if (bossAIState == BossAIState::Caution)
				{
					wavesCount = 0;
				}
			}
			else
			{
				jumpBetTimer++;
			}
		}		
	}
	else
	{
		if (IsFirstPosAround(transform_.position_))
		{
			transform_.position_.x = firstPos.x;
			transform_.position_.z = firstPos.z;
			AttackVariableReset(BossAttackState::JumpAttack);
		}
		else
		{// �����ʒu�ɖ߂�

			ReturnFirstPos();
		}
	}
}

void EnemyBoss::SpecialAttackAction()
{
	const float JUMP_ATK_JUMP_STEP = 0.25f;	// �W�����v�U���O�̕ω���(�㏸��)
	const float MAX_HEIGHT = 10.0f;		// �ō����B�n�_

	// ���f���Ŕ͈͂�����������
	if (pSpecialArea == nullptr)
	{
		pSpecialArea = Instantiate<EnemyBossSpecialArea>(GetParent());

		if (GetSceneID() == SCENE_ID::SCENE_ID_BATTLE)
		{
			// �T�E���h�ύX
			BattleScene* pBattleScene = (BattleScene*)FindObject("BattleScene");
			pBattleScene->ChangeBossSound();
		}
	}


	// �ō����B�n�_�ɂ��������ǂ���
	if (transform_.position_.y + jumpSpeed < MAX_HEIGHT)
	{
		// �㏸����
		jumpSpeed += JUMP_ATK_JUMP_STEP;
		transform_.position_.y += jumpSpeed;
	}
	else
	{
		// �ō����B�n�_�ɂ������~������
		transform_.position_.y = MAX_HEIGHT;
	}

	// ���s�O���Ԃ𒴂�����U�����s��
	if (specialTimer >= TIME_UP_TO_SPECIAL_ATTACK)
	{		
		// �n�ʂɒ��n������
		transform_.position_.y = firstPos.y;

		// �������f���̏���
		pSpecialArea->KillMe();
		pSpecialArea = nullptr;


		// �U������
		pPlayer = (Player*)FindObject("Player");
		CharacterDamageCalculation(CharacterID::EnemyBoss, CharacterID::Player, 0, SPECIAL_ATK_MAGNIFICATION);
		pPlayer->SetDamageStage(DamageStage::DamageStart);


		AttackVariableReset(BossAttackState::SpecialAttack);
	}
	else
	{
		specialTimer++;
	}
}

void EnemyBoss::AttackVariableReset(BossAttackState nowState)
{
	switch (nowState)
	{
	case BossAttackState::NoAttack:
		break;
	case BossAttackState::BulletAttack:
		bulletCount = 0;
		bulletTimer = 0;
		break;
	case BossAttackState::SpiralMoveAttack:
		isEndLine = false;
		isDrawPolyLine = false;
		spiralAngle = 0;
		spiralRadius = 0;
		break;
	case BossAttackState::WavesAttack:
		wavesCount = 0;
		wavesJumpTimer = 0;
		jumpSpeed = 0;
		break;
	case BossAttackState::JumpAttack:
		jumpBetTimer = 0;
		jumpSpeed = 0;
		jumpCount = 0;
		isPointGetting = false;
		break;
	case BossAttackState::SpecialAttack:
		specialTimer = 0;
		jumpSpeed = 0;
		break;
	default:
		break;
	}

	ClearAttackState(nowState);
	ChangeAttackState(BossAttackState::NoAttack);
}

void EnemyBoss::ReturnFirstPos()
{
	const float MOVE_SPEED = 0.125f;	// �x�N�g���̒���(�ړ���)�𒲐�����

	XMVECTOR vMyPos = XMLoadFloat3(&transform_.position_);
	XMVECTOR vCenter = XMLoadFloat3(&firstPos);

	// �����ʒu�Ɍ������x�N�g����p��
	XMVECTOR vMove = vCenter - vMyPos;
	XMVector3Normalize(vMove);
	vMove *= MOVE_SPEED;

	XMFLOAT3 moveNow;
	XMStoreFloat3(&moveNow, vMove);

	//�ړ�����
	transform_.position_.x += moveNow.x;
	transform_.position_.z += moveNow.z;
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

#ifdef _DEBUG

	// �s���ɂ���(�Q�[�W�͂����ʂ茸�炷��0�ɂ͂Ȃ�Ȃ�)
	if (isImmortality)
	{
		hp -= damage;
		pGauge->Damage(damage);
		if (hp <= 0)
		{
			hp = 1;
		}
		return;
	}

#endif

	

	// ����U�����s���Ă��Ȃ��̂ɁA�̗͂�����U���J�n�������Ȃ��Ȃ�Ȃ��悤�ɂ���
	if (isSpecialAttack == false && hp - damage <= maxHp / RATE_FOR_MAX_STRENGTH)
	{
		// ���g���C���̓Q�[�W�����C���܂Ō��炷
		if (hp == maxHp)
		{
			pGauge->Damage(damage);
		}

		hp = maxHp / RATE_FOR_MAX_STRENGTH;
	}
	else
	{
		hp -= damage;
		totalDamages += damage;
		pGauge->Damage(damage);
	}
	
	

	// ���ȏ�_���[�W��^�����AI���x�����ő��Ԃ���Ȃ��Ƃ��Ɉ�i�K�グ��
	if (totalDamages >= TOTAL_DAMAGES_UP_AI_LEVEl && bossAIState != BossAIState::Caution)
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
	if (hp <= 0)
	{
		Leave();
	}
}

void EnemyBoss::DrawEffect()
{
	if (isDrawPolyLine)
	{
		pLine->Draw();
	}
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
			// �U���{���̐ݒ�
			float attackMagnification = 0;

			for (unsigned int nowState = (unsigned int)BossAttackState::NoAttack; nowState <= (unsigned int)BossAttackState::MaxAttackState; nowState++)
			{
				BossAttackState nowAttack = (BossAttackState)nowState;

				switch (nowAttack)
				{
				case BossAttackState::NoAttack:
					break;
				case BossAttackState::SpiralMoveAttack:
					attackMagnification = SPIRAL_MOVE_ATK_MAGNIFICATION;
					break;
				case BossAttackState::JumpAttack:
					attackMagnification = JUMP_ATK_MAGNIFICATION;
					break;
				default:
					break;
				}
			}
			
			// �v���C���[���_���[�W���󂯂Ă��Ȃ�������_���[�W�������s�킹��
			if (pPlayer->GetDamageState() == DamageStage::NoDamage && attackMagnification != 0)
			{
				CharacterDamageCalculation(CharacterID::EnemyBoss, CharacterID::Player, 0, attackMagnification);
				pPlayer->SetDamageStage(DamageStage::DamageStart);
				pPlayer->SetDamageDirection(-(GetFrontVector()));
			}
		}
		
	}


	if (pTarget->GetObjectName() == "RobotBullet")
	{
		CharacterDamageCalculation(CharacterID::Robot, CharacterID::EnemyBoss);
		SetDamageStage(DamageStage::DamageStart);

		pTarget->KillMe();
	}
}

void EnemyBoss::AttackModelDamageToPlayer(BossAttackModelHandle attackSource, XMVECTOR vec)
{
	pPlayer = (Player*)FindObject("Player");

	// �U���{���̐ݒ�
	float attackMagnification = 0;

	// ���f���n���h���ʂɔ{����ݒ�
	switch (attackSource)
	{
	case BossAttackModelHandle::Bullet:
		attackMagnification = BULLET_ATK_MAGNIFICATION;
		break;
	case BossAttackModelHandle::Wave:
		attackMagnification = WAVES_ATK_MAGNIFICATION;
		break;
	default:
		break;
	}

	// �v���C���[���_���[�W���󂯂Ă��Ȃ�������_���[�W�������s�킹��
	if (pPlayer->GetDamageState() == DamageStage::NoDamage && attackMagnification != 0)
	{
		CharacterDamageCalculation(CharacterID::EnemyBoss, CharacterID::Player, 0, attackMagnification);
		pPlayer->SetDamageStage(DamageStage::DamageStart);
		pPlayer->SetDamageDirection(vec);		
	}
}

bool EnemyBoss::BossEntry()
{
	const float FAIL_SPEED = 0.5f;

	// �`���������
	Visible();

	if (pWarning == nullptr)
	{
		// Warning�̉摜������
		pWarning = Instantiate<Warning>(GetParent());
	}

	if (transform_.position_.y > ENTRY_POS_Y)
	{
		transform_.position_.y -= FAIL_SPEED;
		return false;
	}
	else
	{
		transform_.position_.y = ENTRY_POS_Y;
		pWarning->KillMe();
		pWarning = nullptr;
		return true;
	}
}

void EnemyBoss::ProcessStart()
{
	pGauge = Instantiate<EnemyBossGauge>(GetParent());

	// �X�V������������
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

		if (IsAttackState(nowAttack) && isTrueAttackState == false)
		{
			isTrueAttackState = true;
		}
	}

	if (isTrueAttackState == false)
	{
		ChangeAttackState(BossAttackState::NoAttack);
	}
}

bool EnemyBoss::IsFirstPosAround(XMFLOAT3 pos)
{
	const float POS_ERROR_RANGE = 0.025f;			// �����ʒu�̌덷�͈�

	if (pos.x * pos.x + pos.z * pos.z <= POS_ERROR_RANGE)
	{
		return true;
	}

	return false;
}

bool EnemyBoss::DiedAction()
{
	if (GraduallyTransparency())
	{
		pEffect->StopEffectDead();
		return true;
	}
	else if (pEffect->IsCalledDeadEffect() == false)
	{
		pEffect->SetCalledDeadFlg();

		// Effect�̌Ăяo��
		pEffect->SetEmitterPosition(GetPosition(), EmitterType::Dead);
		pEffect->StartEffectDead();
	}

	return false;
}
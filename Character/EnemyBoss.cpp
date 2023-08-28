#include "EnemyBoss.h"
#include "../UI/EnemyBossGauge.h"

#include "Player.h"
#include "../AttackModel/EnemyBossBullet.h"
#include "../AttackModel/EnemyBossWaves.h"
#include "../AttackModel/EnemyBossJumpArea.h"
#include "../AttackModel/EnemyBossSpecialArea.h"
#include "../UI/Warning.h"
#include "../Scene/BattleScene.h"
#include "../Scene/SceneManager.h"

// 定数宣言
const XMFLOAT3 HIT_TEST_RANGE_OUTSIDE = { 18, 9,18 };	//outsideの当たり判定枠
const XMFLOAT3 HIT_TEST_RANGE_INSIDE = { 12, 9, 12 };	//insideの当たり判定枠
const FLOAT ENTRY_FALL_SPEED = 1.6f;

EnemyBoss::EnemyBoss(GameObject* parent)
	: EnemyBase(parent, "EnemyBoss")
{
	pPlayer = nullptr;
	pGauge = nullptr;

	bossAttackState = (unsigned int)BossAttackState::NoAttack;
	bossAIState = BossAIState::Allowance;
	
	attackIntervalTimer = 0;


	bulletTimer = 0;
	bulletCount = 0;

	hp = 0;

	pWarning = nullptr;

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
	BULLET_ATK_INTERVAL_TIME = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::BulletAtkIntervalTime);
	BULLET_ATK_MAX_COUNT = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::BulletAtkMaxCount);
	BULLET_ATK_MAGNIFICATION = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::BulletAtkMagnification);
	WAVES_ATK_MAX_COUNT = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::WavesAtkMaxCount);
	WAVES_ATK_MAGNIFICATION = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::WavesAtkMagnification);
	JUMP_ATK_MAX_COUNT = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::JumpAtkMaxCount);
	JUMP_ATK_BET_TIMER = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::JumpAtkBetTimer);
	JUMP_ATK_MAGNIFICATION = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::JumpAtkMagnification);
	TIME_UP_TO_SPECIAL_ATTACK = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::TimeUpToSpecialAttack);
	SPECIAL_ATK_MAGNIFICATION = GetInternalData(CharacterID::EnemyBoss, (int)EnemyBossData::SpecialAtkMagnification);

}

void EnemyBoss::Initialize()
{
	SetData();
	SetParameter(CharacterID::EnemyBoss);

	CharacterModelLoad("enemyBoss.fbx");
	
	CharacterAddCollider(HIT_TEST_RANGE_OUTSIDE);
	CharacterAddCollider(HIT_TEST_RANGE_INSIDE);


	// 変数の初期化
	{
		// 着地点のy座標を設定
		ENTRY_POS_Y = transform_.position_.y;
		firstPos = transform_.position_;
		transform_.position_.y = ENTRY_FIRST_POS_Y;


		hp = GetParameterValue(CharacterID::EnemyBoss, CharacterStatus::HP);
		maxHp = hp;

		// 各種該当状態を拒否
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

	// AIレベルで攻撃間隔時間を変動させる
	if (attackIntervalTimer >= ATTACK_INTERVAL_TIME / (int)bossAIState)
	{
		attackIntervalTimer = 0;

		AttackTypeSelection();
		ChangeState(CharacterState::Attacking);
	}

	// 最大体力に対して現在体力の割合が一定以下になったら特殊攻撃を行う
	if (isSpecialAttack == false && hp <= maxHp / RATE_FOR_MAX_STRENGTH)
	{
		SecondFormStart();
	}
}

void EnemyBoss::SecondFormStart()
{
	// リトライ時に呼ばれたらHPを減少させる
	if (hp == maxHp)
	{
		float reHP = maxHp - (maxHp / RATE_FOR_MAX_STRENGTH);
		Damage(reHP);
	}
	
	
	isSpecialAttack = true;
	attackIntervalTimer = 0;

	// AI状態を最大状態にする
	bossAIState = BossAIState::Caution;

	// 特殊攻撃を行う
	ChangeAttackState(BossAttackState::SpecialAttack);

	ChangeState(CharacterState::Attacking);
}

void EnemyBoss::AttackTypeSelection()
{
	int type = 0;

#ifdef _DEBUG

	// 動作確認用
	bossAIState = BossAIState::Caution;
	ChangeAttackState(BossAttackState::JumpAttack);
	return;

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
			ChangeAttackState(BossAttackState::JumpAttack);	// WavesAttackも同時に行う
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

		// 前後左右に弾を出す
		BulletAttackCal("FRONT");
		BulletAttackCal("BACK");
		BulletAttackCal("RIGHT");
		BulletAttackCal("LEFT");


		bulletCount++;
	}

	// 攻撃を終えるかどうかの確認
	if (bulletCount == BULLET_ATK_MAX_COUNT)
	{
		AttackVariableReset(BossAttackState::BulletAttack);
	}
}

void EnemyBoss::BulletAttackCal(std::string dirName)
{
	const float LENGTH_HALF = 0.5f;	// 移動ベクトルの長さ調整

	EnemyBossBullet* pBullet = Instantiate<EnemyBossBullet>(GetParent());

	XMFLOAT3 rootPos, tipPos;			// ボーンポジション用
	XMFLOAT3 moveDir;					// 進行方向

	rootPos = Model::GetBonePosition(GetCharacterModel(), dirName + "_Root");
	tipPos = Model::GetBonePosition(GetCharacterModel(), dirName + "_Tip");

	XMVECTOR vRoot = XMLoadFloat3(&rootPos);
	XMVECTOR vTip = XMLoadFloat3(&tipPos);

	XMVECTOR vMove = vTip - vRoot;
	if (dirName == "BACK")
	{
		vMove *= -1;	// 後ろ方向の時はベクトルの向きを反転
	}
	vMove = XMVector3Normalize(vMove);

	vMove *= LENGTH_HALF;

	XMStoreFloat3(&moveDir, vMove);

	pBullet->SetPosition(tipPos);
	pBullet->SetMoveDirection(moveDir);
}

void EnemyBoss::SpiralMoveAttackAction()
{
	const float RADIUS_STEP = 1.7f;				// 半径の増加率
	const float ANGLE_STEP = 0.05f;				// 回転角度の増加率
	const float MOVING_MAGNIFICATION = 0.05f;	// 移動量倍率
	
	// 位置設定用変数
	float nextPosX, nextPosZ;

	if (isEndLine)
	{// 内側に狭まる
		spiralAngle -= ANGLE_STEP;
		spiralRadius -= RADIUS_STEP;

		nextPosX = spiralRadius * sin(spiralAngle);
		nextPosZ = spiralRadius * cos(spiralAngle);
	}
	else
	{// 外側に広がる
		spiralAngle += ANGLE_STEP;
		spiralRadius += RADIUS_STEP;

		nextPosX = spiralRadius * cos(spiralAngle);
		nextPosZ = spiralRadius * sin(spiralAngle);
	}

	
	

	// 螺旋移動
	transform_.position_.x = nextPosX * MOVING_MAGNIFICATION;
	transform_.position_.z = nextPosZ * MOVING_MAGNIFICATION;

	// 端に到達したかどうか
	if (IsMoveLimit(transform_.position_) && isEndLine == false)
	{
		isEndLine = true;
	}

	// 初期位置周辺に戻ってきたかどうか
	if (isEndLine && IsFirstPosAround(transform_.position_))
	{
		transform_.position_ = firstPos;
		AttackVariableReset(BossAttackState::SpiralMoveAttack);
	}

}

void EnemyBoss::WavesAttackAction()
{
	const int WAVES_ATK_BEFORE_TIME = 60;		// 攻撃前の時間
	const float WAVES_JUMP_SPEED_STEP = 0.0125f;	// 攻撃前のジャンプ増加値

	if (wavesCount < WAVES_ATK_MAX_COUNT)
	{
		// 上昇させる
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

			// 床に着地
			transform_.position_.y -= PositionAdjustment(transform_.position_);

			// 波状攻撃を行う
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
	const float JUMP_ATK_JUMP_STEP = 0.25f;	// ジャンプ攻撃前の変化量(上昇量)

	if (jumpCount < JUMP_ATK_MAX_COUNT)
	{// 攻撃処理


		if (jumpBetTimer < JUMP_ATK_BET_TIMER)
		{// 上昇処理
			jumpBetTimer++;

			// 着地地点の情報を取得したかどうか
			if (isPointGetting == false)
			{
				isPointGetting = true;

				// モデルで落ちる場所を可視化させる
				pPlayer = (Player*)FindObject("Player");
				landingPosition = pPlayer->GetPosition();
				pArea = Instantiate<EnemyBossJumpArea>(GetParent());
				pArea->SetArea(landingPosition);
			}

			jumpSpeed += JUMP_ATK_JUMP_STEP;
			transform_.position_.y += jumpSpeed;

		}
		else
		{// 着地処理
			
			transform_.position_.x = landingPosition.x;
			transform_.position_.y -= PositionAdjustment(transform_.position_);
			transform_.position_.z = landingPosition.z;

			// AIレベルが最大だったら波状攻撃も行う
			if (bossAIState == BossAIState::Caution && wavesCount == 0)
			{
				// 波状攻撃開始
				EnemyBossWaves* pWaves = Instantiate<EnemyBossWaves>(GetParent());
				pWaves->SetStartPos(transform_.position_);
				wavesCount++;
			}

			// 可視化させたモデルを消す
			if (pArea != nullptr)
			{
				pArea->KillMe();
				pArea = nullptr;
			}

			// ジャンプ攻撃後に少し停止させる(前後のカウントのため二倍にする)
			if (jumpBetTimer > JUMP_ATK_BET_TIMER * 2)
			{
				// 変数を更新して次のジャンプ攻撃を行わせる
				jumpBetTimer = 0;
				jumpSpeed = 0;
				isPointGetting = false;
				jumpCount++;

				// AIレベルが最大の時は波状攻撃の変数も更新する
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
			transform_.position_ = firstPos;
			AttackVariableReset(BossAttackState::JumpAttack);
		}
		else
		{// 初期位置に戻る

			ReturnFirstPos();
		}
	}
}

void EnemyBoss::SpecialAttackAction()
{
	const float JUMP_ATK_JUMP_STEP = 0.25f;	// ジャンプ攻撃前の変化量(上昇量)
	const float MAX_HEIGHT = 10.0f;		// 最高到達地点

	// モデルで範囲を可視化させる
	if (pSpecialArea == nullptr)
	{
		pSpecialArea = Instantiate<EnemyBossSpecialArea>(GetParent());

		if (GetSceneID() == SCENE_ID::SCENE_ID_BATTLE)
		{
			// サウンド変更
			BattleScene* pBattleScene = (BattleScene*)FindObject("BattleScene");
			pBattleScene->ChangeBossSound();
		}
	}


	// 最高到達地点にいったかどうか
	if (transform_.position_.y + jumpSpeed < MAX_HEIGHT)
	{
		// 上昇処理
		jumpSpeed += JUMP_ATK_JUMP_STEP;
		transform_.position_.y += jumpSpeed;
	}
	else
	{
		// 最高到達地点についたら停止させる
		transform_.position_.y = MAX_HEIGHT;
	}

	// 実行前時間を超えたら攻撃を行う
	if (specialTimer >= TIME_UP_TO_SPECIAL_ATTACK)
	{		
		// 地面に着地させる
		transform_.position_.y = firstPos.y;

		// 可視化モデルの消去
		pSpecialArea->KillMe();
		pSpecialArea = nullptr;


		// 攻撃処理
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
	const float MOVE_SPEED = 0.125f;	// ベクトルの長さ(移動量)を調整する

	XMVECTOR vMyPos = XMLoadFloat3(&transform_.position_);
	XMVECTOR vCenter = XMLoadFloat3(&firstPos);

	// 初期位置に向かうベクトルを用意
	XMVECTOR vMove = vCenter - vMyPos;
	XMVector3Normalize(vMove);
	vMove *= MOVE_SPEED;

	XMFLOAT3 moveNow;
	XMStoreFloat3(&moveNow, vMove);

	//移動処理
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
	pGauge->Damage(damage);
	hp -= damage;
	totalDamages += damage;

	// 一定以上ダメージを与えられAIレベルが最大状態じゃないときに一段階上げる
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
			// 攻撃倍率の設定
			float atackMagnification = 1.0f;

			for (unsigned int nowState = (unsigned int)BossAttackState::NoAttack; nowState <= (unsigned int)BossAttackState::MaxAttackState; nowState++)
			{
				BossAttackState nowAttack = (BossAttackState)nowState;

				switch (nowAttack)
				{
				case BossAttackState::NoAttack:
					break;
				case BossAttackState::JumpAttack:
					atackMagnification = JUMP_ATK_MAGNIFICATION;
					break;
				default:
					break;
				}

			}
			
			// プレイヤーがダメージを受けていなかったらダメージ処理を行わせる
			if (pPlayer->GetDamageState() == DamageStage::NoDamage)
			{
				CharacterDamageCalculation(CharacterID::EnemyBoss, CharacterID::Player, 0, atackMagnification);
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

	// 攻撃倍率の設定
	float atackMagnification = 1.0f;

	// モデルハンドル別に倍率を設定
	switch (attackSource)
	{
	case BossAttackModelHandle::Bullet:
		atackMagnification = BULLET_ATK_MAGNIFICATION;
		break;
	case BossAttackModelHandle::Wave:
		atackMagnification = WAVES_ATK_MAGNIFICATION;
		break;
	default:
		break;
	}

	// プレイヤーがダメージを受けていなかったらダメージ処理を行わせる
	if (pPlayer->GetDamageState() == DamageStage::NoDamage)
	{
		CharacterDamageCalculation(CharacterID::EnemyBoss, CharacterID::Player, 0, atackMagnification);
		pPlayer->SetDamageStage(DamageStage::DamageStart);
		pPlayer->SetDamageDirection(vec);

		// 何とのダメージ判定処理なのかをLogで出力
		
	}
}

bool EnemyBoss::BossEntry()
{
	const float FAIL_SPEED = 0.5f;

	// 描画を許可する
	Visible();

	if (pWarning == nullptr)
	{
		// Warningの画像初期化
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

	// 更新処理を許可する
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
	const float POS_ERROR_RANGE = 0.025f;			// 初期位置の誤差範囲

	if (pos.x * pos.x + pos.z * pos.z <= POS_ERROR_RANGE)
	{
		return true;
	}

	return false;
}
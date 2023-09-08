#include "Player.h"

#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/Global.h"

#include "../Effect/PolyLine.h"
#include "../Effect/Effect.h"

#include "../UI/PlayerGauge.h"
#include "../UI/RecoveryPotion.h"

#include "../Scene/DebugScene.h"

#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"
#include "../Manager/EnemyManager.h"

#include "../Sound/GameSound.h"

// 定数宣言
const XMFLOAT3 HIT_TEST_RANGE = { 4, 4, 4 };	// 当たり判定枠
const float JUMP_FIRST_SPEED = 1.4f;			// ジャンプの初速度

void Player::SetData()
{
	STRENGTH_RATE_INCREASING_ATTACK = GetInternalData(CharacterID::Player, (int)PlayerData::StrengthRateIncreasingAttack);
	ATTACK_POWER_INCREASE_RATE = GetInternalData(CharacterID::Player, (int)PlayerData::AttackPowerIncreaseRate);
	NORMAL_ATTACK_INCREASE_RATE = GetInternalData(CharacterID::Player, (int)PlayerData::NormalAttackIncreaseRate);
	HARD_ATTACK_INCREASE_RATE = GetInternalData(CharacterID::Player, (int)PlayerData::HardAttackIncreaseRate);
	NORMAL_ATTACK_TIME = GetInternalData(CharacterID::Player, (int)PlayerData::NormalAttackTime);
	HARD_ATTACK_TIME = GetInternalData(CharacterID::Player, (int)PlayerData::HardAttackTime);
	DODGE_TIME = GetInternalData(CharacterID::Player, (int)PlayerData::DodgeTime);
	RECOVERY_POTION_NUMBER = GetInternalData(CharacterID::Player, (int)PlayerData::RecoveryPotionNumber);
	RECOVERY_QUANTITY = GetInternalData(CharacterID::Player, (int)PlayerData::RecoveryQuantity);
	MAX_DAMAGE_TIMER = GetInternalData(CharacterID::Player, (int)PlayerData::MaxDamageTimer);
}

Player::Player(GameObject* parent)
	:CharacterBase(parent, "Player")
{
	STRENGTH_RATE_INCREASING_ATTACK = 0;
	ATTACK_POWER_INCREASE_RATE = 0;
	NORMAL_ATTACK_INCREASE_RATE = 0;
	HARD_ATTACK_INCREASE_RATE = 0;
	NORMAL_ATTACK_TIME = 0;
	HARD_ATTACK_TIME = 0;
	DODGE_TIME = 0;
	RECOVERY_POTION_NUMBER = 0;
	RECOVERY_QUANTITY = 0;
	MAX_DAMAGE_TIMER = 0;

	pGauge = nullptr;
	pPotion = nullptr;
	hRecoveryEffect = -1;
	hp = 0;

	isTrrigerReset = true;
	isInputReception = true;

	movingDistance = { 0,0,0 };
	vPrevPos = { 0,0,0,0 };

	beforeJumpY = 0;
	jumpSpeed = 0;
	isJumpSummit = false;

	pEffect = nullptr;
	attackState = AttackState::NoAttack;
	attackTimer = 0;
	attackVector = { 0,0,0,0 };

	pLine = nullptr;
	dodgeTimer = 0;

	damageTimer = 0;
	vTraveling = { 0,0,0,0 };

	angleX = 0;
	angleY = 0;
	cameraDirection = { 0,0,0 };
	cameraPosition = { 0,0,0 };
	cameraFocus = { 0,0,0 };

#ifdef _DEBUG
	
	isImmortality = false;

#endif
}

Player::~Player()
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

void Player::Initialize()
{
	SetData();
	SetParameter(CharacterID::Player);

	CharacterModelLoad("player.fbx");
	CharacterAddCollider(HIT_TEST_RANGE);

	// 効果音のロード(回復の効果音のみ番号取得する)
	hRecoveryEffect = SoundEffectLoad(SoundEffect::GaugeRecovery);
	SoundEffectLoad(SoundEffect::NormalAttack);
	SoundEffectLoad(SoundEffect::HardAttack);


	// 変数の初期化
	{
		transform_.position_.z = -45.0f;
		vPrevPos = XMLoadFloat3(&transform_.position_);

		hp = GetParameterValue(CharacterID::Player, CharacterStatus::HP);
		jumpSpeed = JUMP_FIRST_SPEED;

		pGauge = Instantiate<PlayerGauge>(GetParent());
		
		pLine = new PolyLine();
		pLine->Load("Effect/tex.png");

		pEffect = new Effect();

		pPotion = Instantiate<RecoveryPotion>(GetParent());
		pPotion->SetPotionCount(RECOVERY_POTION_NUMBER);

	}

	NormalCamera();
}

void Player::Release()
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

void Player::CharacterUpdate()
{
	//カメラ設定
	NormalCamera();

	if (GetHP() > 0)
	{
		// 回避を再度行える用になったかどうか
		float trrigerR = Input::GetPadTrrigerR();
		if (trrigerR == 0)
			isTrrigerReset = true;

		// 回復
		if (IsRecoverEntry())	HPRecovery(RECOVERY_QUANTITY);

		// 現在の状態関係なく行えるアクション
		if (IsDodEntry())	ChangeState(CharacterState::Dodging);
			


		// 特定の状態じゃないときに使えるアクション
		{
			// 攻撃中は使用できないアクション
			if (IsStateSet(CharacterState::Attacking) == false)
			{
				if (IsJumpEntry())	ChangeState(CharacterState::Jumping);
				if (IsMoveEntry())	ChangeState(CharacterState::Moving);
			}
			else
			{
				// 状態フラグが立っていたら下げる
				if (IsStateSet(CharacterState::Jumping))	ClearState(CharacterState::Jumping);
				if (IsStateSet(CharacterState::Moving))		ClearState(CharacterState::Moving);

			}

			// ジャンプ中には行えないアクション
			if (IsStateSet(CharacterState::Jumping) == false)
			{
				// 攻撃
				if (IsAttackEntry())	ChangeState(CharacterState::Attacking);
			}
		}

		if (IsStateSet(CharacterState::Jumping) == false)
		{
			transform_.position_.y -= PositionAdjustment(transform_.position_);
		}
	}

	CharacterCheckHP();

}

void Player::CharacterIdleAction()
{
	if (GetHP() > 0)
	{
		// 各状態に応じた入力が行われたら状態を変化させる
		if (IsMoveEntry())
		{
			ChangeState(CharacterState::Moving);
		}
		if (IsDodEntry())
		{
			ChangeState(CharacterState::Dodging);
		}
		if (IsAttackEntry())
		{
			ChangeState(CharacterState::Attacking);
		}
		if (IsJumpEntry())
		{
			ChangeState(CharacterState::Jumping);
		}
	}
	
}

void Player::CharacterMove()
{
	const float MOVING_DISTANCE_ADJUSTMENT = 0.5f;	// プレイヤーの移動量の調節


	XMFLOAT3 move = Input::GetPadStickL();
	if (Input::IsKey(DIK_W)) move.y += 1;
	if (Input::IsKey(DIK_A)) move.x -= 1;
	if (Input::IsKey(DIK_S)) move.y -= 1;
	if (Input::IsKey(DIK_D)) move.x += 1;


	// 入力が行われていなかったら状態を下す
	if (move.x == 0 && move.y == 0 || isInputReception == false)
	{
		ClearState(CharacterState::Moving);
		return;
	}

	XMVECTOR travelingDirection = XMVectorSet(move.x, 0, move.y, 0);
	vPrevPos = XMLoadFloat3(&transform_.position_);

	// カメラの横方向回転が行われていたらプレイヤーのベクトルを変形させる
	if (angleX != 0)
	{
		XMMATRIX mRotateX = XMMatrixRotationY(angleX);
		travelingDirection = XMVector3TransformCoord(travelingDirection, mRotateX);
	}

	// 移動量を設定
	travelingDirection = XMVector3Normalize(travelingDirection);
	travelingDirection *= MOVING_DISTANCE_ADJUSTMENT;
	XMStoreFloat3(&movingDistance, travelingDirection);


	XMFLOAT3 nextPos = movingDistance;
	nextPos.x += transform_.position_.x;
	nextPos.z += transform_.position_.z;

	if (IsMoveLimit(nextPos))
	{
		XMStoreFloat3(&transform_.position_, vPrevPos);
	}
	else
	{
		// 移動処理
		transform_.position_.x += movingDistance.x;
		transform_.position_.z += movingDistance.z;
	}

	// モデルの回転
	if (movingDistance.x != 0 || movingDistance.z != 0)
	{
		transform_.rotate_.y = (float)atan2(movingDistance.x, movingDistance.z) * DEGREES_180 / M_PI;
	}
}

void Player::CharacterAttack()
{
	switch (attackState)
	{
	case AttackState::NoAttack:
		ClearState(CharacterState::Attacking);
		break;
	case AttackState::NormalAttack:
		NormalAttackAction();
		break;
	case AttackState::HardAttack:
		HardAttackAction();
		break;
	default:
		break;
	}
}

void Player::NormalAttackAction()
{
	// エフェクト
	pEffect->SetEmitterPosition(transform_.position_, EmitterType::Ventilation);
	XMFLOAT3 dir = { 0,0,0 };
	XMStoreFloat3(&dir, GetFrontVector());
	pEffect->SetDirection(dir, transform_.rotate_);
	pEffect->StartEffectAtNormalAttack();

	if (attackTimer > NORMAL_ATTACK_TIME)
	{
		pEffect->StopEffectAtNormalAttack();
		SoundEffectStop(SoundEffect::NormalAttack);
		attackTimer = 0;
		attackState = AttackState::NoAttack;
	}
	else
	{
		attackTimer++;
	}
}

void Player::HardAttackAction()
{
	const float ANGLE_ROTATE_HARD_ATTACK = 12.0f;	// 強攻撃時の回転する角度

	// エフェクト
	pEffect->SetEmitterPosition(transform_.position_, EmitterType::Tornado);
	pEffect->StartEffectAtHardAttack();

	if (attackTimer > HARD_ATTACK_TIME)
	{
		pEffect->StopEffectAtHardAttack();
		SoundEffectStop(SoundEffect::HardAttack);
		attackTimer = 0;
		attackState = AttackState::NoAttack;
	}
	else
	{
		attackTimer++;
		transform_.rotate_.y += ANGLE_ROTATE_HARD_ATTACK;
	}
}

void Player::CharacterCheckHP()
{
	if (hp <= 0)
	{
		SetInputReception(false);
	}

	// 回復の効果音が再生終了していたら停止処理を行う
	if (IsSoundEffectStop(SoundEffect::GaugeRecovery, hRecoveryEffect))
	{
		SoundEffectStop(SoundEffect::GaugeRecovery);
	}
}

void Player::CharacterTakeDamage(float damage)
{
	DamageStage nowStage = GetDamageState();

	if (IsStateSet(CharacterState::Dodging))
	{// 攻撃を受けたときにプレイヤーの状態が回避状態だったなら判定無しでダメージ処理を終える
		nowStage = DamageStage::EndDamage;
	}

	switch (nowStage)
	{
	case DamageStage::NoDamage:
		ClearState(CharacterState::Damaged);
		break;
	case DamageStage::DamageStart:
		// HPゲージを減らす
		HPDamage(damage);
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

void Player::DamageMotion()
{
	if (damageTimer <= MAX_DAMAGE_TIMER)
	{
		const float VECTOR_MAGNIFICATION = 0.8f;	// 移動倍率

		damageTimer++;
		ColorChange(1, 0, 0);	// モデルの色変更

		// 進行方向ベクトルの取得、調整
		if ( XMVector3EqualR(vTraveling, XMVectorZero()) )
		{
			// 中身がすべて0だったら自身のベクトルを反転させてセットさせる
			vTraveling = -(GetFrontVector());
		}
		vTraveling *= VECTOR_MAGNIFICATION;

		XMFLOAT3 motionPos = { 0,0,0 };
		XMStoreFloat3(&motionPos, vTraveling);

		motionPos.x += transform_.position_.x;
		motionPos.z += transform_.position_.z;

		if (IsMoveLimit(motionPos) == false)
		{
			vPrevPos = XMLoadFloat3(&transform_.position_);

			transform_.position_.x = motionPos.x;
			transform_.position_.z = motionPos.z;
		}
	}
	else
	{
		damageTimer = 0;
		SetDamageStage(DamageStage::EndDamage);
	}
}

void Player::NormalCamera()
{
	const XMVECTOR VECTOR_FROM_PLAYER_TO_CAMERA = { 0, 3.0f, -32.0f, 0 };	// プレイヤーからみたカメラへのベクトル
	const float VECTOR_LENGTH_UP_TO_FOCUS = 4.5f;	// 焦点までのベクトルのスカラー倍の値

	// カメラの回転角度とベクトル設定
	{
		const float CAMERA_MOUSE_SENSITIVITY = 0.05f;		// カメラの移動量(感度)
		const float CAMERA_ANGLE_SPEED_X = 0.05f;			// カメラの横方向回転スピード
		const float CAMERA_ANGLE_SPEED_Y = 0.0125f;			// カメラの縦方向回転スピード
		const float CAMERA_UPWARD_MAXIMUM_VALUE = 1.0f;		// カメラ上方向の最大値
		const float CAMERA_DOWNWARD_MAXIMUM_VALUE = 0.0f;	// カメラ下方向の最大値

		
		XMFLOAT3 cameraMove;
		if (Input::IsControllerConnected())
		{
			cameraMove = Input::GetPadStickR();
			cameraMove.y *= -1;		// 垂直方向は反転させる
		}
		else
		{
			cameraMove = Input::GetMouseMove();
			cameraMove.x *= CAMERA_MOUSE_SENSITIVITY;
			cameraMove.y *= CAMERA_MOUSE_SENSITIVITY;
		}
		
		// カメラの回転する角度を設定
		angleX += cameraMove.x * CAMERA_ANGLE_SPEED_X;
		angleY += cameraMove.y * CAMERA_ANGLE_SPEED_Y;

		// 垂直方向を制限する
		angleY = min(max(angleY, CAMERA_DOWNWARD_MAXIMUM_VALUE) , CAMERA_UPWARD_MAXIMUM_VALUE);
	}

	// それぞれの回転角度に応じて回転行列を作成
	XMMATRIX mRotateX = XMMatrixRotationY(angleX);	// 水平方向回転行列
	XMMATRIX mRotateY = XMMatrixRotationX(angleY);	// 垂直方向回転行列

	// 行列でベクトルの変形
	XMVECTOR vCamera = VECTOR_FROM_PLAYER_TO_CAMERA;
	vCamera = XMVector3TransformCoord(vCamera, mRotateY);
	vCamera = XMVector3TransformCoord(vCamera, mRotateX);

	// プレイヤーをカメラが追従させるための移動行列作成
	XMMATRIX mMoving = XMMatrixTranslation(movingDistance.x, movingDistance.y, movingDistance.z);

	// プレイヤーのポジションを取得
	XMVECTOR vPosition = XMLoadFloat3(&transform_.position_);

	// カメラに移動行列を適用させる
	XMVECTOR vCameraPosition = XMVector3TransformCoord(vCamera, mMoving);

	// カメラの方向ベクトル
	XMVECTOR cameraVector = XMVector3Normalize(vCameraPosition);
	XMStoreFloat3(&cameraDirection, cameraVector);

	// カメラの位置設定
	vCameraPosition += vPosition;

	// 焦点の位置設定
	XMVECTOR vCameraInverse = -vCamera;
	vCameraInverse = XMVector3Normalize(vCameraInverse) * VECTOR_LENGTH_UP_TO_FOCUS;
	XMVECTOR vCameraFocus = vCameraInverse + vPosition;

	// カメラをセット
	
	XMStoreFloat3(&cameraPosition, vCameraPosition);
	XMStoreFloat3(&cameraFocus, vCameraFocus);


	Camera::SetPosition(cameraPosition);
	Camera::SetTarget(cameraFocus);
}

void Player::CharacterJumpAction()
{
	const float LOWEST_JUMP_VELOCITY_CHANGE_QUANTITY = 0.1f;	// 最低ジャンプ速度変化量
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
		ClearState(CharacterState::Jumping);
	}
}

void Player::CharacterDodingAction()
{
	const float DODGE_MOVING_DISTANCE_MAGNIFICATION = 1.5f;	// 回避移動量倍率

	// 回避コマンドが入ったとき、攻撃中だったら中止する
	if (IsStateSet(CharacterState::Attacking))
	{
		if (attackState == AttackState::NormalAttack)
		{
			pEffect->StopEffectAtNormalAttack();
		}
		else
		{
			pEffect->StopEffectAtHardAttack();
		}

		attackTimer = 0;
		attackState = AttackState::NoAttack;
	}

	// ポリラインに現在ポジションを追加する
	pLine->AddPosition(transform_.position_);

	//　回避処理
	if (dodgeTimer <= DODGE_TIME)
	{
		dodgeTimer++;

		// 回避中はモデルの色を変更させる
		ColorChange(0.5f, 0.5f, 0.8f, 0.5f);

		XMFLOAT3 nextPos = transform_.position_;
		nextPos.x += movingDistance.x * DODGE_MOVING_DISTANCE_MAGNIFICATION;
		nextPos.z += movingDistance.z * DODGE_MOVING_DISTANCE_MAGNIFICATION;

		if (IsMoveLimit(nextPos))
		{
			XMStoreFloat3(&transform_.position_, vPrevPos);
		}
		else
		{
			vPrevPos = XMLoadFloat3(&transform_.position_);

			// 移動
			transform_.position_.x = nextPos.x;
			transform_.position_.z = nextPos.z;
		}
	}
	else
	{
		RestoreOriginalColor();
		dodgeTimer = 0;
		ClearState(CharacterState::Dodging);
	}
}

void Player::CharacterStunAction()
{

}

void Player::DrawEffect()
{
	if (IsStateSet(CharacterState::Dodging))
	{
		pLine->Draw();
	}
}

void Player::OnCollision(GameObject* pTarget, Collider* nowCollider)
{
	if (pTarget->GetObjectName() == "Enemy")
	{
		//XMStoreFloat3(&transform_.position_, vPrevPos);

		if (IsStateSet(CharacterState::Attacking))
		{
			int index = 0;

			for (auto nowEnemy = EnemyManager::enemyList.begin(); nowEnemy < EnemyManager::enemyList.end(); nowEnemy++)
			{
				Enemy* pEnemy = EnemyManager::GetEnemyContent(index);

				if (pEnemy->IsPlayerHitting())
				{
					switch (attackState)
					{
					case AttackState::NoAttack:
						break;
					case AttackState::NormalAttack:
						CharacterDamageCalculation(CharacterID::Player, CharacterID::NormalEnemy, index, NORMAL_ATTACK_INCREASE_RATE);
						break;
					case AttackState::HardAttack:
						CharacterDamageCalculation(CharacterID::Player, CharacterID::NormalEnemy, index, HARD_ATTACK_INCREASE_RATE);
						break;
					default:
						break;
					}

					pEnemy->SetDamageStage(DamageStage::DamageStart);
				}

				index++;
			}
		}
	}

	if (pTarget->GetObjectName() == "EnemyBoss")
	{
		// 今回の当たり判定が外側ではなく内側の当たり判定の枠だったら以前の位置に戻す
		Collider* check = pTarget->GetColliderListFront();
		if (nowCollider != check)
		{
			XMStoreFloat3(&transform_.position_, vPrevPos);
		}

		if (IsStateSet(CharacterState::Attacking))
		{
			EnemyBoss* pBoss = (EnemyBoss*)FindObject("EnemyBoss");
			
			if (pBoss->GetDamageState() == DamageStage::NoDamage)
			{
				switch (attackState)
				{
				case AttackState::NoAttack:
					break;
				case AttackState::NormalAttack:
					CharacterDamageCalculation(CharacterID::Player, CharacterID::EnemyBoss, NORMAL_ATTACK_INCREASE_RATE);
					pBoss->SetDamageStage(DamageStage::DamageStart);
					break;
				case AttackState::HardAttack:
					CharacterDamageCalculation(CharacterID::Player, CharacterID::EnemyBoss, HARD_ATTACK_INCREASE_RATE);
					pBoss->SetDamageStage(DamageStage::DamageStart);
				default:
					break;
				}
			}
			
		}
	}
}

void Player::HPDamage(float value)
{
#ifdef _DEBUG

	// 不死にする(ゲージはいつも通り減らすが0にはならない)
	if (isImmortality)
	{
		hp -= value;
		pGauge->Damage(value);
		if (hp <= 0)
		{
			hp = 1;
		}
		return;
	}

#endif

	hp -= value;
	pGauge->Damage(value);
}

void Player::HPRecovery(float value)
{
	// 現在体力が最大体力より低かったら回復処理を行う
	if (hp < GetParameterValue(CharacterID::Player, CharacterStatus::HP) && pPotion != nullptr)
	{
		hp += value;

		if (hp > GetParameterValue(CharacterID::Player, CharacterStatus::HP))
		{
			hp = GetParameterValue(CharacterID::Player, CharacterStatus::HP);
		}
		SoundEffectPlay(SoundEffect::GaugeRecovery);
		pGauge->Recovery(value);
		pPotion->DawnPotionNumber();
		
		if (pPotion->GetPotionCount() == 0)
		{
			pPotion->KillMe();
			pPotion = nullptr;
		}
	}
}

bool Player::IsMoveEntry()
{
	if (isInputReception)
	{
		if (Input::GetPadStickL().x != 0 ||
			Input::GetPadStickL().y != 0 ||
			Input::IsKeyDown(DIK_W) ||
			Input::IsKeyDown(DIK_A) ||
			Input::IsKeyDown(DIK_S) ||
			Input::IsKeyDown(DIK_D))
		{
			return true;
		}
	}

	return false;
}

bool Player::IsDodEntry()
{
	if (isInputReception)
	{

		if (isTrrigerReset && Input::GetPadTrrigerR() != 0 || Input::IsKeyDown(DIK_LSHIFT))
		{
			isTrrigerReset = false;
			return true;
		}
	}
	return false;
}

bool Player::IsAttackEntry()
{
	if (isInputReception)
	{
		if (attackState == AttackState::NoAttack)
		{
			// 通常攻撃
			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B) || Input::IsMouseButtonDown(MouseBottunCode::LeftClick))
			{
				attackState = AttackState::NormalAttack;
				SoundEffectPlay(SoundEffect::NormalAttack);
				return true;
			}

			// 強攻撃
			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y) || Input::IsMouseButtonDown(MouseBottunCode::RightClick))
			{
				attackState = AttackState::HardAttack;
				SoundEffectPlay(SoundEffect::HardAttack);

				return true;
			}
		}
	}

	return false;
}

bool Player::IsRecoverEntry()
{
	if (isInputReception)
	{
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X) || Input::GetMouseMove().z != 0)
		{
			return true;
		}
	}
	return false;
}

bool Player::IsJumpEntry()
{
	if (isInputReception)
	{
		if (IsStateSet(CharacterState::Jumping) == false)
		{
			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_SPACE))
			{
				beforeJumpY = transform_.position_.y;
				return true;
			}
		}
	}
	
	return false;
}

bool Player::DiedAction()
{
	if (GraduallyTransparency())
	{
		pEffect->StopEffectDead();
		return true;
	}
	else if(pEffect->IsCalledDeadEffect() == false)
	{
		pEffect->SetCalledDeadFlg();

		// Effectの呼び出し
		pEffect->SetEmitterPosition(GetPosition(), EmitterType::Dead);
		pEffect->StartEffectDead();
	}

	return false;
}

void Player::BlowAway()
{
	const float MOVING_DISTANCE_ADJUSTMENT = 1.5f;	// プレイヤーの移動量の調節


	// 進行方向ベクトルを用意する
	XMVECTOR vNowPosition = XMVectorSet(transform_.position_.x, 0, transform_.position_.z, 0);
	XMVECTOR vCenter = XMVectorSet(0, 0, 0, 0);
	XMVECTOR dir = XMVector3Normalize(vNowPosition - vCenter) * MOVING_DISTANCE_ADJUSTMENT;


	XMFLOAT3 moveValue = { 0,0,0 };
	XMStoreFloat3(&moveValue, dir);

	moveValue = Transform::Float3Add(moveValue, transform_.position_);
	

	if (IsMoveLimit(moveValue) == false)
	{
		transform_.position_ = moveValue;
	}
}
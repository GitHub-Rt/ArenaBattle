#include "Player.h"

#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/Global.h"

#include "../Effect/PolyLine.h"
#include "../Effect/PlayerEffect.h"

#include "../UI/Gauge.h"

#include "../Scene/DebugScene.h"
#include "../Character/Enemy.h"

// 定数宣言
const XMFLOAT3 HIT_TEST_RANGE = { 1, 2, 1 };	// 当たり判定枠
const float JUMP_FIRST_SPEED = 1.4f;			// ジャンプの初速度
const XMFLOAT3 GaugePos = XMFLOAT3(-0.95f, 0.88f, 0);
const XMFLOAT3 GaugeScale = XMFLOAT3(1.5f, 1.5f, 1.0f);

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


	pGauge = nullptr;

	hp = 0;


	isTrrigerReset = true;


	movingDistance = XMFLOAT3(0, 0, 0);
	vPrevPos = { 0,0,0,0 };

	beforeJumpY = 0;
	jumpSpeed = 0;

	pEffect = nullptr;
	attackState = AttackState::NoAttack;
	attackTimer = 0;
	attackVector = { 0,0,0,0 };

	pLine = nullptr;
	dodgeTimer = 0;

	damageTimer = 0;

	angleX = 0;
	angleY = 0;
	cameraDirection = XMFLOAT3(0, 0, 0);
}

Player::~Player()
{

}

void Player::Initialize()
{
	SetData();
	SetParameter(CharacterID::Player);

	CharacterModelLoad("player.fbx");
	CharacterAddCollider(HIT_TEST_RANGE);

	
	// 変数の初期化
	{
		transform_.position_.z = -45.0f;
		vPrevPos = XMLoadFloat3(&transform_.position_);

		

		hp = GetParameterValue(CharacterID::Player, CharacterStatus::HP);
		jumpSpeed = JUMP_FIRST_SPEED;


		pGauge = Instantiate<Gauge>(GetParent());
		pGauge->SetGaugeScale(GaugeScale);
		pGauge->SetGaugePosition(GaugePos.x, GaugePos.y);
		pGauge->SetMaxHP(hp);


		pLine = new PolyLine();
		pLine->Load("Effect/Player/tex.png");

		pEffect = new PlayerEffect();
	}

	NormalCamera();
}

void Player::Release()
{
	pLine->Release();
	pEffect->Release();

	SAFE_DELETE(pLine);
	SAFE_DELETE(pEffect);
}

void Player::CharacterUpdate()
{
	//カメラ設定
	NormalCamera();

	float trrigerR = Input::GetPadTrrigerR();
	if (trrigerR == 0)
	{
		isTrrigerReset = true;
	}

	// 現在の状態関係なく行えるアクション
	{
		if (IsDodEntry())
		{
			// 回避
			ChangeState(CharacterState::Dodging);
		}
	}

	// 特定の状態じゃないときに使えるアクション
	{
		// 攻撃中は使用できないアクション
		if (IsStateSet(CharacterState::Attacking) == false)
		{
			// ジャンプ
			if (IsJumpEntry())
			{
				ChangeState(CharacterState::Jumping);
			}

			// 移動
			if (IsMoveEntry())
			{
				ChangeState(CharacterState::Moving);
			}
		}
		else
		{
			// 状態フラグが立っていたら下げる
			if (IsStateSet(CharacterState::Jumping))
			{
				ClearState(CharacterState::Jumping);
			}

			if (IsStateSet(CharacterState::Moving))
			{
				ClearState(CharacterState::Moving);
			}
		}

		// ジャンプ中には行えないアクション
		if (IsStateSet(CharacterState::Jumping) == false)
		{
			if (IsAttackEntry())
			{
				// 攻撃
				ChangeState(CharacterState::Attacking);
			}
		}
	}

	if (IsStateSet(CharacterState::Jumping) == false)
	{
		transform_.position_.y -= PositionAdjustment(transform_.position_);
	}
}

void Player::CharacterIdleAction()
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

void Player::CharacterMove()
{
	const float MOVING_DISTANCE_ADJUSTMENT = 0.5f;	// プレイヤーの移動量の調節

	XMFLOAT3 move = Input::GetPadStickL();
	if (move.x == 0 && move.y == 0)
	{
		ClearState(CharacterState::Moving);
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
	const float VECTOR_LENGTH_AT_NORMAL_ATTACK = 0.5f;	// 通常攻撃時のベクトルの長さ

	// エフェクト
	pEffect->SetEmitterPosition(transform_.position_, EmitterType::Ventilation);
	XMFLOAT3 dir = { 0,0,0 };
	XMStoreFloat3(&dir, GetFrontVector());
	pEffect->SetDirection(dir, transform_.rotate_);
	pEffect->StartEffectAtNormalAttack();


	// 方向のベクトルを取得して移動量に変換
	attackVector = GetFrontVector();
	attackVector *= VECTOR_LENGTH_AT_NORMAL_ATTACK;
	XMFLOAT3 motionPos;
	XMStoreFloat3(&motionPos, attackVector);

	motionPos.x += transform_.position_.x;
	motionPos.z += transform_.position_.z;

	if (attackTimer > NORMAL_ATTACK_TIME)
	{
		pEffect->StopEffectAtNormalAttack();
		attackTimer = 0;
		attackState = AttackState::NoAttack;
	}
	else
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
		ColorChange(1, 0, 0);	// モデルの色変更
		SetDamageStage(DamageStage::TakeDamage);
		break;
	case DamageStage::TakeDamage:
		DamageTakenMotion();
		break;
	case DamageStage::EndDamage:
		RestoreOriginalColor();
		SetDamageStage(DamageStage::NoDamage);
		break;
	default:
		break;
	}

	
}

void Player::DamageTakenMotion()
{
	if (damageTimer <= MAX_DAMAGE_TIMER)
	{
		const float VECTOR_MAGNIFICATION = 0.8f;	// 移動倍率

		damageTimer++;

		// 進行方向ベクトルを取得
		XMVECTOR vTraveling = -(GetFrontVector());
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
	const XMVECTOR VECTOR_FROM_PLAYER_TO_CAMERA = { 0, 3.0f, -30.0f, 0 };	// プレイヤーからみたカメラへのベクトル
	const float VECTOR_LENGTH_UP_TO_FOCUS = 4.5f;	// 焦点までのベクトルのスカラー倍の値

	// カメラの回転角度とベクトル設定
	{
		const float MOUSE_OPERATIONG_RANGE = 1.0f;			// マウスの稼働範囲
		const float CAMERA_ANGLE_SPEED_X = 0.05f;			// カメラの横方向回転スピード
		const float CAMERA_ANGLE_SPEED_Y = 0.025f;			// カメラの縦方向回転スピード
		const float CAMERA_UPWARD_MAXIMUM_VALUE = 1.0f;		// カメラ上方向の最大値
		const float CAMERA_DOWNWARD_MAXIMUM_VALUE = 0.0f;	// カメラ下方向の最大値

#ifdef NDEBUG
		XMFLOAT3 mouseMove = Input::GetMouseMove();

		// マウスの稼働範囲を一定にする
		if (mouseMove.x > MOUSE_OPERATIONG_RANGE)
		{
			mouseMove.x = 1;
		}
		else if (mouseMove.x < -MOUSE_OPERATIONG_RANGE)
		{
			mouseMove.x = -1;
		}

		if (mouseMove.y > MOUSE_OPERATIONG_RANGE)
		{
			mouseMove.y = 1;
		}
		else if (mouseMove.y < -MOUSE_OPERATIONG_RANGE)
		{
			mouseMove.y = -1;
		}
#endif
		// カメラの回転する角度を設定
		// 水平方向回転
		if (Input::GetPadStickR().x > 0
#ifdef NDEBUG
			|| mouseMove.x > 0
#endif
			)
		{
			angleX += CAMERA_ANGLE_SPEED_X;
		}
		else if (Input::GetPadStickR().x < 0
#ifdef NDEBUG
			|| mouseMove.x < 0
#endif
			)
		{
			angleX -= CAMERA_ANGLE_SPEED_X;
		}

		// 垂直方向回転
		if (Input::GetPadStickR().y < 0
#ifdef NDEBUG
			|| mouseMove.y < 0
#endif
			)
		{
			angleY += CAMERA_ANGLE_SPEED_Y;
			if (angleY > CAMERA_UPWARD_MAXIMUM_VALUE)
			{
				angleY = CAMERA_UPWARD_MAXIMUM_VALUE;
			}
		}
		else if (Input::GetPadStickR().y > 0
#ifdef NDEBUG
			|| mouseMove.y > 0
#endif
			)
		{
			angleY -= CAMERA_ANGLE_SPEED_Y;
			if (angleY < CAMERA_DOWNWARD_MAXIMUM_VALUE)
			{
				angleY = CAMERA_DOWNWARD_MAXIMUM_VALUE;
			}
		}
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

	// カメラの方向ベクトルを保存
	XMVECTOR cameraVector = XMVector3Normalize(vCameraPosition);
	XMStoreFloat3(&cameraDirection, cameraVector);

	// カメラの位置設定
	vCameraPosition += vPosition;

	// 焦点の位置設定
	XMVECTOR vCameraInverse = -vCamera;
	vCameraInverse = XMVector3Normalize(vCameraInverse) * VECTOR_LENGTH_UP_TO_FOCUS;
	XMVECTOR vCameraFocus = vCameraInverse + vPosition;

	// カメラをセット
	XMFLOAT3 cameraPosition, cameraFocus;
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

		ColorChange(0, 0, 1, 0.5f);

		XMFLOAT3 nextPos = transform_.position_;
		nextPos.x += movingDistance.x * DODGE_MOVING_DISTANCE_MAGNIFICATION;
		nextPos.z += movingDistance.z * DODGE_MOVING_DISTANCE_MAGNIFICATION;

		if (IsMoveLimit(nextPos))
		{
			XMStoreFloat3(&transform_.position_, vPrevPos);
		}
		else
		{
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

void Player::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Enemy")
	{
		XMStoreFloat3(&transform_.position_, vPrevPos);

		if (IsStateSet(CharacterState::Attacking))
		{
			CharacterDamageCalculation(CharacterID::Player, CharacterID::NormalEnemy, NORMAL_ATTACK_INCREASE_RATE);

			DebugScene* pDebug = (DebugScene*)FindObject("DebugScene");
			Enemy* pEnemy[ENEMY_COUNT];
			pDebug->SetEnemyPointer(pEnemy);

			for (int i = 0; i < ENEMY_COUNT; i++)
			{
				if (pEnemy[i] != nullptr && pEnemy[i]->IsPlayerHitting())
				{
					pEnemy[i]->SetDamageStage(DamageStage::DamageStart);

				}
			}
		}
	}
}

void Player::HPDamage(float value)
{
	hp -= value;
	pGauge->Damage(value);
}

void Player::HPRecovery(float value)
{
	hp += value;
	pGauge->Recovery(value);
}

bool Player::IsMoveEntry()
{
	// コントローラー用
	XMFLOAT3 move = Input::GetPadStickL();
	if (move.x != 0 || move.y != 0)
	{
		return true;
	}
	return false;
}

bool Player::IsDodEntry()
{
	// コントローラー用
	float trrigerR = Input::GetPadTrrigerR();
	if (isTrrigerReset && trrigerR != 0)
	{
		isTrrigerReset = false;
		return true;
	}
	return false;
}

bool Player::IsAttackEntry()
{
	if (attackState == AttackState::NoAttack)
	{
		// 通常攻撃
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B)
#ifdef NDEBUG
			|| Input::IsMouseButtonDown(MouseBottunCode::LeftClick)
#endif
			)
		{
			attackState = AttackState::NormalAttack;
			//pSound->EffectPlay(SoundEffect::NormalAttack);
			return true;
		}

		// 強攻撃
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y)
#ifdef NDEBUG
			|| Input::IsMouseButtonDown(MouseBottunCode::RightClick)
#endif
			)
		{
			attackState = AttackState::HardAttack;
			//pSound->EffectPlay(SoundEffect::HardAttack);
			
			return true;
		}
	}

	return false;
}

bool Player::IsRecoverEntry()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_X) 
#ifdef NDEBUG
		|| Input::GetMouseMove().z != 0)
#endif
		)
	{
		return true;
	}
	return false;
}

bool Player::IsJumpEntry()
{
	if (IsStateSet(CharacterState::Jumping) == false)
	{

		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A)
#ifdef NDEBUG
			|| Input::IsKeyDown(DIK_SPACE)
#endif	
			)
		{
			beforeJumpY = transform_.position_.y;
			return true;
		}
	}

	return false;
}



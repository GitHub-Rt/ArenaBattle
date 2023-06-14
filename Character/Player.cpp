#include "Player.h"

#include "../Engine/Input.h"
#include "../Engine/Camera.h"

// 定数宣言




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
	MAX_INVINCIBLE_TIME = GetInternalData(CharacterID::Player, (int)PlayerData::MaxInvincibleTime);
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
	MAX_INVINCIBLE_TIME = 0;

	attackState = AttackState::NoAttack;


	isTrrigerReset = true;


	movingDistance = XMFLOAT3(0, 0, 0);
	vPrevPos = { 0,0,0,0 };

	angleX = 0;
	angleY = 0;
	cameraDirection = XMFLOAT3(0, 0, 0);
}

Player::~Player()
{

}

void Player::Initialize()
{
	CharacterModelLoad("player.fbx");

	transform_.position_.z = -45.0f;
	vPrevPos = XMLoadFloat3(&transform_.position_);

	NormalCamera();
}

void Player::Release()
{
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

	if (GetState() != CharacterState::Jumping)
	{
		transform_.position_.y -= PositionAdjustment(transform_.position_);
	}
}

void Player::CharacterIdleAction()
{
	// 各状態に応じた入力が行われたら状態を変化させる
	if (IsMoveEntry()) {
		ChangeState(CharacterState::Moving);
	}
	if (IsDodEntry())
	{
		ChangeState(CharacterState::Doding);
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
		ChangeState(CharacterState::Idle);
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

	// 移動処理
	transform_.position_.x += movingDistance.x;
	transform_.position_.z += movingDistance.z;

	// モデルの回転
	if (movingDistance.x != 0 || movingDistance.z != 0)
	{
		transform_.rotate_.y = (float)atan2(movingDistance.x, movingDistance.z) * DEGREES_180 / M_PI;
	}
}

void Player::CharacterAttack()
{

}

void Player::CharacterCheckHP()
{
}

void Player::CharacterTakeDamage(float damage)
{
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

}

void Player::CharacterDodingAction()
{

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
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A)
#ifdef NDEBUG
		|| Input::IsKeyDown(DIK_SPACE)
#endif	
		)
	{
		return true;
	}
	return false;
}

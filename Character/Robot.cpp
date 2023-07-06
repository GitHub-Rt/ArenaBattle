#include "Robot.h"
#include "Player.h"

#include "../Engine/Input.h"

#include "../AttackModel/RobotBullet.h"


// �萔�錾

// �v���C���[����݂��ʒu�̑����l
const float POS_X = 0.5f;
const float POS_Y = 0.5f;
const float POS_Z = -2.5f;
const float MOVESPEED = 0.25f;		// �v���C���[�̈ړ��ɂ��Ă����Ƃ��̃X�s�[�h



void Robot::SetData()
{
	BETWEEN_BULLETTIMER = GetInternalData(CharacterID::Robot, (int)RobotData::BulletTimer);
}

Robot::Robot(GameObject* parent)
	:CharacterBase(parent, "Robot")
{
	BETWEEN_BULLETTIMER = 0;

	pPlayer = nullptr;
	bulletTimer = 0;
}

Robot::~Robot()
{

}

void Robot::Initialize()
{
	CharacterModelLoad("robot.fbx");

	pPlayer = (Player*)FindObject("Player");

	SetParameter(CharacterID::Robot);
	SetData();

	// �����ʒu�ݒ�
	{
		XMFLOAT3 playerPos = pPlayer->GetPosition();
		playerPos.x += POS_X;
		playerPos.y += POS_Y;
		playerPos.z += POS_Z;

		transform_.position_.x += playerPos.x;
		transform_.position_.y += playerPos.y;
		transform_.position_.z += playerPos.z;
	}
}

void Robot::Release() 
{
}

void Robot::CharacterUpdate()
{
	SetAngle();

	CharacterMove();

	if (pPlayer->IsStateSet(CharacterState::Idle) && IsStateSet(CharacterState::Moving))
	{
		ClearState(CharacterState::Moving);
	}
	
	// �e�U���̐؂�ւ�
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_RIGHT_SHOULDER) || Input::IsKeyDown(DIK_LCONTROL))
	{
		if (IsStateSet(CharacterState::Attacking))
		{
			bulletTimer = 0;
			ClearState(CharacterState::Attacking);
		}
		else
		{
			ChangeState(CharacterState::Attacking);
		}
	}

	// �{�X�̓o�ꒆ(�v���C���[�����͂��s���Ȃ��Ƃ�)�͍U����Ԃ���߂�
	if (pPlayer->IsInputReception() == false)
	{
		bulletTimer = 0;
		ClearState(CharacterState::Attacking);
	}
}

void Robot::CharacterMove()
{
	XMFLOAT3 playerPos = pPlayer->GetPosition();
	playerPos.x += POS_X;
	playerPos.y += POS_Y;
	playerPos.z += POS_Z;

	if (transform_.position_.x != playerPos.x ||
		transform_.position_.z != playerPos.z)
	{
		ChangeState(CharacterState::Moving);

		XMFLOAT3 nowPos = GetPosition();
		XMVECTOR vNowPos = XMLoadFloat3(&nowPos);
		XMVECTOR vPoint = XMLoadFloat3(&playerPos);
		XMVECTOR vMove = vPoint - vNowPos;
		XMVector3Normalize(vMove);
		vMove *= MOVESPEED;

		XMFLOAT3 move;
		XMStoreFloat3(&move, vMove);


		transform_.position_.x += move.x;
		transform_.position_.z += move.z;
	}
	else
	{
		ClearState(CharacterState::Moving);
	}
}

void Robot::CharacterAttack()
{
	bulletTimer++;
	if (bulletTimer >= BETWEEN_BULLETTIMER)
	{
		bulletTimer = 0;

		RobotBullet* pBullet = Instantiate<RobotBullet>(GetParent());

		XMFLOAT3 root = Model::GetBonePosition(GetCharacterModel(), "root");
		XMFLOAT3 tip = Model::GetBonePosition(GetCharacterModel(), "tip");

		XMVECTOR vRoot = XMLoadFloat3(&root);
		XMVECTOR vTip = XMLoadFloat3(&tip);

		XMVECTOR vMove = vTip - vRoot;
		vMove = XMVector3Normalize(vMove);

		XMFLOAT3 move;
		XMStoreFloat3(&move, vMove);

		pBullet->SetPosition(tip);
		pBullet->SetMoveDirection(move);
	}
	
}

void Robot::SetAngle()
{
	// �J�����̕����x�N�g�����擾
	XMFLOAT3 cameraDirection = pPlayer->GetCameraDirection();
	cameraDirection.y = 0;

	// ���f���̕����x�N�g����ݒ�
	XMFLOAT3 modelDirection = { 0, 0, -1 };

	// ���ꂼ��̕����x�N�g���𐳋K������
	XMVECTOR vCameraDirection = XMVector3Normalize(XMLoadFloat3(&cameraDirection));
	XMVECTOR vModelDirection = XMVector3Normalize(XMLoadFloat3(&modelDirection));

	// ��̃x�N�g���̓��ς����߂�
	XMVECTOR vDot = XMVector3Dot(vCameraDirection, vModelDirection);
	float rad = acos(XMVectorGetX(vDot));

	XMVECTOR vCross = XMVector3Cross(vCameraDirection, vModelDirection);
	float cross = XMVectorGetY(vCross);
	if (cross > 0)
	{
		rad *= -1;
	}
	// ���W�A�� �� �x�ɕϊ�
	float angle = rad * DEGREES_180 / M_PI;

	// ��]
	transform_.rotate_.y = (float)angle;
}

void Robot::CharacterIdleAction()
{
	if (pPlayer->IsStateSet(CharacterState::Moving))
	{
		ChangeState(CharacterState::Moving);
	}
}

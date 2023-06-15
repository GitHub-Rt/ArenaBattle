#pragma once
#include "AttackModelBase.h"

class Robot;

class RobotBullet : public AttackModelBase
{
public:
	RobotBullet(GameObject* parent);
	~RobotBullet();
	void Initialize() override;
	void AttackModelUpdate() override;

	// �����ʒu�ݒ�
	void InitialPositionPreference();

	// �i�s�������Z�b�g
	void SetMoveDirection(XMFLOAT3 direction) { travelingDirection = direction; }

	// �|�W�V�������Z�b�g
	void SetPosition(XMFLOAT3 pos) { transform_.position_ = pos; }


	void SetAttackPower(float value) override;

private:

	Robot* pRobot;
	int timer;						// ����
	XMFLOAT3 travelingDirection;	// �i�s����
	float attackPower;				// �U����
};


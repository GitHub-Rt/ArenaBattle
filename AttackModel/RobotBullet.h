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

	// 初期位置設定
	void InitialPositionPreference();

	// 進行方向をセット
	void SetMoveDirection(XMFLOAT3 direction) { travelingDirection = direction; }

	// ポジションをセット
	void SetPosition(XMFLOAT3 pos) { transform_.position_ = pos; }

private:

	Robot* pRobot;
	int timer;						// 時間
	XMFLOAT3 travelingDirection;	// 進行方向

};


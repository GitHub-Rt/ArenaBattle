#pragma once
#include "AttackModelBase.h"

class EnemyBossJumpArea : public AttackModelBase
{
public:
	EnemyBossJumpArea(GameObject* parent);
	~EnemyBossJumpArea();
	void Initialize() override;
	void AttackModelUpdate() override;
	void Draw() override;

	// ���������邽�߂̏���
	void SetArea(XMFLOAT3 pos);
	

private:
	Transform moveArea;

	int hModelFloor;	// ���̃��f���n���h��
	int hModelCircle;	// �������~�̃��f���n���h��

	int scaleTimer;		// �g�k�v���^�C�}�[
};


#include "EnemyBossJumpArea.h"


EnemyBossJumpArea::EnemyBossJumpArea(GameObject* parent)
	: AttackModelBase(parent, "EnemyBossJumpArea")
{
	moveArea = Transform();
}

EnemyBossJumpArea::~EnemyBossJumpArea()
{

}

void EnemyBossJumpArea::Initialize()
{
	hModelFloor = AttackModelLoadInt("enemyBossJumpFloor.fbx");
	hModelCircle = AttackModelLoadInt("enemyBossJumpArea.fbx");
}

void EnemyBossJumpArea::AttackModelUpdate()
{
	const int SCALE_TIME = 30;			// �g�傷�鎞��
	const int SCALEDOWN_TIME = 60;		// �k�����鎞��
	const float SCALING_STEP = 0.29f;	// �g��k����


	


	scaleTimer++;
	if (scaleTimer < SCALE_TIME)
	{
		moveArea.scale_.x += SCALING_STEP;
		moveArea.scale_.z += SCALING_STEP;
	}
	else if (scaleTimer < SCALEDOWN_TIME)
	{
		moveArea.scale_.x -= SCALING_STEP;
		moveArea.scale_.z -= SCALING_STEP;
	}
	else
	{
		scaleTimer = 0;
	}
}

void EnemyBossJumpArea::Draw()
{
	AttackModelDraw(hModelFloor, transform_);
	AttackModelDraw(hModelCircle, moveArea);
}


void EnemyBossJumpArea::SetArea(XMFLOAT3 pos)
{
	const float POS_Y_ADJUSTMENT = 0.25f;	// y���W�̔�����

	transform_.position_ = pos;
	transform_.position_.y -= PositionAdjustment(transform_.position_) - POS_Y_ADJUSTMENT;


	moveArea = transform_;
}
#include "EnemyBossSpecialArea.h"

EnemyBossSpecialArea::EnemyBossSpecialArea(GameObject* parent)
	: AttackModelBase(parent, "EnemyBossSpecialArea")
{
	scaleTimer = 0;
}

EnemyBossSpecialArea::~EnemyBossSpecialArea()
{

}

void EnemyBossSpecialArea::Initialize()
{
	const float POS_Y_ADJUSTMENT = 0.25f;	// yç¿ïWÇÃî˜í≤êÆ

	AttackModelLoad("enemyBossJumpArea.fbx");
	transform_.position_.y -= PositionAdjustment(transform_.position_) - POS_Y_ADJUSTMENT;
}

void EnemyBossSpecialArea::AttackModelUpdate()
{
	const float SCALING_STEP = 2.5f;	// ägèkíiäK
	const int SCAL_TIME = 20;			// ägëÂéûä‘
	const int SCALDOWN_TIME = 40;		// èkè¨éûä‘

	scaleTimer++;
	
	if (scaleTimer < SCAL_TIME)
	{
		transform_.scale_.x += SCALING_STEP;
		transform_.scale_.z += SCALING_STEP;
	}
	else if (scaleTimer < SCALDOWN_TIME)
	{
		transform_.scale_.x -= SCALING_STEP;
		transform_.scale_.z -= SCALING_STEP;
	}
	else
	{
		// ëÂÇ´Ç≥Çèâä˙ílÇ…ñﬂÇ∑
		transform_.scale_ = XMFLOAT3(1, 1, 1);
		scaleTimer = 0;
	}
}
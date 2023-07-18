#include "EnemyBossJumpArea.h"

#include "../Character/EnemyBoss.h"

EnemyBossJumpArea::EnemyBossJumpArea(GameObject* parent)
	: AttackModelBase(parent, "EnemyBossJumpArea")
{

}

EnemyBossJumpArea::~EnemyBossJumpArea()
{

}

void EnemyBossJumpArea::Initialize()
{

}

void EnemyBossJumpArea::AttackModelUpdate()
{

}

void EnemyBossJumpArea::Draw()
{

}


void EnemyBossJumpArea::SetArea(XMFLOAT3 pos)
{
	transform_.position_ = pos;
	moveArea = transform_;
}
#include "BattleBackGround.h"

BattleBackGround::BattleBackGround(GameObject* parent)
	: StageBase(parent, "BattleBackGround")
{

}

BattleBackGround::~BattleBackGround()
{

}

void BattleBackGround::Initialize()
{
	StageModelLoad("BattleBackGround.fbx");

	transform_.position_.y += 65;
}

void BattleBackGround::Draw()
{
	StageDraw(transform_);
}
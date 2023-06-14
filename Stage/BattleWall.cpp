#include "BattleWall.h"

BattleWall::BattleWall(GameObject* parent)
	:StageBase(parent, "StageBase")
{

}

BattleWall::~BattleWall()
{

}

void BattleWall::Initialize()
{
	StageModelLoad("Stage/BattleWall.fbx");
}
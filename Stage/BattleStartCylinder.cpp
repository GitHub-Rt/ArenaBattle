#include "BattleStartCylinder.h"
#include "../Scene/PlayScene.h"

BattleStartCylinder::BattleStartCylinder(GameObject* parent)
	: StageBase(parent, "BattleStartCylinder")
{
	pScene = nullptr;
}

BattleStartCylinder::~BattleStartCylinder()
{

}

void BattleStartCylinder::Initialize()
{
	pScene = (PlayScene*)FindObject("PlayScene");

	StageModelLoad("start.fbx");
	
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(5, 60, 5));
	AddCollider(collision);
}

void BattleStartCylinder::Draw()
{
	StageDraw(transform_);
}

void BattleStartCylinder::OnCollision(GameObject* pTarget, Collider* nowCollider)
{
	if (pTarget->GetObjectName() == "Player")
	{
		pScene->BattleStart();
	}
}
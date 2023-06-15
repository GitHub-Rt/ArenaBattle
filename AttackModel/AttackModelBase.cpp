#include "AttackModelBase.h"

#include "../Engine/Model.h"

#include "../Scene/SceneManager.h"

AttackModelBase::AttackModelBase(GameObject* parent, std::string fileName)
	: GameObject(parent, fileName)
{
	hModel = -1;
}

AttackModelBase::~AttackModelBase()
{

}

void AttackModelBase::Update()
{
	if (IsEntered())
	{
		AttackModelUpdate();
	}
}

void AttackModelBase::Draw()
{
	AttackModelDraw(hModel);
}

void AttackModelBase::Release()
{

}

void AttackModelBase::AttackModelLoad(std::string fileName)
{
	hModel = Model::Load("AttackModel/" + fileName);
	assert(hModel >= 0);
}

void AttackModelBase::AttackModelDraw(int modelHandle)
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void AttackModelBase::AttackModelAddBoxCollider(XMFLOAT3 size, XMFLOAT3 center)
{
	BoxCollider* myCollision = new BoxCollider(center, size);
	AddCollider(myCollision);
}

void AttackModelBase::AttackModelAddSphereCollider(float radius, XMFLOAT3 center)
{
	SphereCollider* myCollision = new SphereCollider(center, radius);
	AddCollider(myCollision);
}

bool AttackModelBase::IsMoveLimit(XMFLOAT3 nextPosition)
{
	const float MOVE_LIMIT = 75.0f;

	if (nextPosition.x > MOVE_LIMIT ||
		nextPosition.x < -MOVE_LIMIT ||
		nextPosition.z > MOVE_LIMIT ||
		nextPosition.z < -MOVE_LIMIT)
	{
		return true;
	}

	return false;
}

SCENE_ID AttackModelBase::GetSceneID()
{
	SceneManager* pManager = (SceneManager*)FindObject("SceneManager");
	return pManager->GetSceneID();
}
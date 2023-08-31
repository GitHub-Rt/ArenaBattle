#include "AttackModelBase.h"

#include "../Engine/Model.h"

#include "../Scene/SceneManager.h"
#include "../Stage/StageBase.h"

#include "../Character/EnemyBoss.h"


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
	std::string objName = this->GetObjectName();
	
	if (pBoss == nullptr)
	{
		pBoss = (EnemyBoss*)FindObject("EnemyBoss");
	}

	if (objName == "RobotBullet")
	{
		AttackModelUpdate();
	}
	else if (pBoss->IsEntered())
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

int AttackModelBase::AttackModelLoadInt(std::string fileName)
{
	hModel = Model::Load("AttackModel/" + fileName);
	assert(hModel >= 0);

	return hModel;
}

void AttackModelBase::AttackModelDraw(int modelHandle)
{
	Model::SetTransform(modelHandle, transform_);
	Model::Draw(modelHandle);
}

void AttackModelBase::AttackModelDraw(int modelHandle, Transform trans)
{
	Model::SetTransform(modelHandle, trans);
	Model::Draw(modelHandle);
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

float AttackModelBase::PositionAdjustment(XMFLOAT3 position)
{
	const float START_PLUS_Y = 100;	// 高い位置からレイを発射させるため
	const XMFLOAT3 RAY_DIRECTION = { 0,-1,0 };	// レイの方向


	SCENE_ID nowScene = GetSceneID();
	StageBase* pStage = nullptr;

	switch (nowScene)
	{
	case SCENE_ID::SCENE_ID_BATTLE:
	case SCENE_ID::SCENE_ID_DEBUG:
		pStage = (StageBase*)FindObject("Stage");
		break;
	case SCENE_ID::SCENE_ID_PLAY:
		pStage = (StageBase*)FindObject("NormalField");
		break;
	default:
		break;
	}

	if (pStage != nullptr)
	{
		int groundHundle = pStage->GetModelHandle();


		RayCastData data;
		data.start = position;
		data.start.y += START_PLUS_Y;
		data.dir = RAY_DIRECTION;
		Model::RayCast(groundHundle, &data);

		if (data.hit)
		{
			// 高くした値を取り除いて返す
			return data.dist - START_PLUS_Y;
		}
	}
}

bool AttackModelBase::IsObjectUnder(XMFLOAT3 position, int handle)
{
	RayCastData data;
	data.start = position;
	data.dir = { 0,-1,0 };
	Model::RayCast(handle, &data);

	if (data.hit)
	{
		return true;
	}

	return false;
}
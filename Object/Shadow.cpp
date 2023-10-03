#include "Shadow.h"
#include "../Engine/Model.h"
#include "../Scene/SceneManager.h"

#include "../Stage/StageBase.h"

Shadow::Shadow(GameObject* parent)
	:GameObject(parent, "Shadow")
{
	hModel = -1;
	parentObj = parent;
	pManager = nullptr;
}

Shadow::~Shadow()
{

}

void Shadow::Initialize()
{
	hModel = Model::Load("Object/shadow.fbx");
	assert(hModel >= 0);

	pManager = (SceneManager*)FindObject("SceneManager");
	SetShadow();
}

void Shadow::Update()
{
}

void Shadow::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Shadow::Release()
{
	KillMe();
}

void Shadow::SetShadow()
{
	// 親オブジェクトの下に影として設置する
	if (parentObj != nullptr)
	{
		XMFLOAT3 pos = parentObj->GetPosition();
		SCENE_ID nowScene = pManager->GetSceneID();

		StageBase* pStage = nullptr;

		switch (nowScene)
		{
		case SCENE_ID::SCENE_ID_PLAY:
			pStage = (StageBase*)FindObject("NormalField");
			break;
		case SCENE_ID::SCENE_ID_BATTLE:
		case SCENE_ID::SCENE_ID_DEBUG:
			pStage = (StageBase*)FindObject("Stage");
			break;
		default:
			break;
		}


		if (pStage != nullptr)
		{
			const XMFLOAT3 RAY_DIRECTION = XMFLOAT3(0, -1, 0);

			int groundHundle = pStage->GetModelHandle();

			RayCastData data;
			data.start = pos;
			data.dir = RAY_DIRECTION;
			Model::RayCast(groundHundle, &data);

			if (data.hit)
			{
				transform_.position_.y = pos.y - data.dist;
			}
		}


	}
}
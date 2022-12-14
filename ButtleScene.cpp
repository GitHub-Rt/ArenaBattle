#include "ButtleScene.h"

#include "Player.h"
#include "Wall.h"
#include "Enemy.h"
#include "Stage.h"
#include "NormalField.h"
#include "EnemyBoss.h"


#include "Engine/SceneManager.h"

//デバッグ用
#include "Engine/Input.h"

//コンストラクタ
ButtleScene::ButtleScene(GameObject* parent)
	: GameObject(parent, "ButtleScene")
{
}

//初期化
void ButtleScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Wall>(this);
	Instantiate<NormalField>(this);
	Instantiate<Player>(this);

	for (int i = 0; i < eNum; i++)
	{
		//Instantiate<Enemy>(this);
	}
		

	Instantiate<Enemy>(this);
	
}

//更新
void ButtleScene::Update()
{
	if (FindObject("Enemy") == nullptr && isBoss == false)
	{
		isBoss = true;
		Instantiate<EnemyBoss>(this);
	}

	if (FindObject("EnemyBoss") == nullptr && isBoss == true)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}

	if (FindObject("Player") == nullptr)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_OVER);
	}



	//デバッグ用
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_BACK, 0))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void ButtleScene::Draw()
{
}

//開放
void ButtleScene::Release()
{
}
#include "ButtleScene.h"

#include "../Player/Player.h"
#include "../Player/HP_Gauge.h"
#include "../Stage/Wall.h"
#include "../Enemy/Enemy.h"
#include "../Stage/Stage.h"
#include "../Stage/NormalField.h"
#include "../Enemy/Boss/EnemyBoss.h"



#include "SceneManager.h"

#include "../imgui/imguiObject.h"


#ifdef _DEBUG

#include "../Engine/Input.h"

#endif
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
	Instantiate<HP_Gauge>(this);

	for (int i = 0; i < eNum; i++)
	{
		//Instantiate<Enemy>(this);
	}
		

	//Instantiate<Enemy>(this);

	Instantiate<imguiObject>(this);
	
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


#ifdef _DEBUG

	//プレイシーンへ戻る(Backボタン)
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_BACK, 0))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}

	//プレイヤーの体力をぎりぎりにする(Startボタン)
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START, 0))
	{
		Player* pPlayer = (Player*)FindObject("Player");
		pPlayer->SetDying();
	}


	//プレイヤーを無敵状態にする(Start,Backボタン同時)
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START, 0) && Input::IsPadButtonDown(XINPUT_GAMEPAD_BACK, 0))
	{
		Player* pPlayer = (Player*)FindObject("Player");
		pPlayer->SetInvincible();
	}

	

#endif
}

//描画
void ButtleScene::Draw()
{
}

//開放
void ButtleScene::Release()
{
}
#include "DebugScene.h"
#include "../Stage/Stage.h"

#include "../imgui/imguiObject.h"
#include "../Stage/BattleBackGround.h"
#include "../Stage/BattleWall.h"

#include "../Stage/WaterFloor.h"

#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"
#include "../Manager/EnemyManager.h"

#include "../Scene/SceneManager.h"
#include "../Engine/Input.h"

// 定数宣言
const int EnemyTimer = 30;	// 敵が全滅してから再登場するまでのフレーム数
const int ENEMY_COUNT = 3;


DebugScene::DebugScene(GameObject* parent)
	: GameObject(parent, "DebugScene")
{
	pPlayer = nullptr;
	pBoss = nullptr;
	pPlayer = nullptr;
	timer = 0;
}

void DebugScene::Initialize()
{
	//SceneManager* pManager = (SceneManager*)FindObject("SceneManager");
	//pManager->SetHardModeFlg();

	/*if (EnemyManager::IsListEmpty() == false)
	{
		EnemyManager::ClearEnemy();
	}*/
	
	Instantiate<Stage>(this);
	Instantiate<BattleWall>(this);
	//Instantiate<BattleBackGround>(this);
	Instantiate<WaterFloor>(this);

	/*for (int i = 0; i < ENEMY_COUNT; i++)
	{
		EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	}*/
	pBoss = Instantiate<EnemyBoss>(this);
	pBoss->ProcessStart();

	// 第二形態からスタートさせる
	///pBoss->SecondFormStart();
	
	pPlayer = Instantiate<Player>(this);
	Instantiate<Robot>(this);

	Instantiate<imguiObject>(this);
}

void DebugScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) || Input::IsKeyDown(DIK_ESCAPE))
	{
		PostQuitMessage(0);	//プログラム終了
	}

	//// 敵がすべて倒されたら一定時間経過後、再登場する
	//if (EnemyManager::IsListEmpty())
	//{
	//	timer++;
	//	if (timer > EnemyTimer)
	//	{
	//		timer = 0;
	//		
	//		for (int i = 0; i < ENEMY_COUNT; i++)
	//		{
	//			EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	//		}
	//	}		
	//}

	//if (pBoss->IsEntered() == false && EnemyManager::IsListEmpty())
	//{
	//	// プレイヤーの入力を受け付けなくする
	//	pPlayer->SetInputReception(false);
	//	if (pBoss->BossEntry())
	//	{
	//		// プレイヤーの入力受付を再開する
	//		pPlayer->SetInputReception(true);
	//		pBoss->ProcessStart();
	//	}
	//}

	//if (pPlayer->GetHP() <= 0)
	//{
	//	SceneManager* pManager = (SceneManager*)FindObject("SceneManager");
	//	pManager->ReLoadScene(SCENE_ID::SCENE_ID_DEBUG);
	//}
	//else if (pBoss->GetHP() <= 0)
	//{
	//	SceneManager* pManager = (SceneManager*)FindObject("SceneManager");
	//	pManager->ReLoadScene(SCENE_ID::SCENE_ID_DEBUG);
	//}
}

void DebugScene::Draw()
{

}

void DebugScene::Release()
{

}


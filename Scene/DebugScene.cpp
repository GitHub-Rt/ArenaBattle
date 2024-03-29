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
	timer = 0;
}

void DebugScene::Initialize()
{
	SceneManager* pManager = (SceneManager*)FindObject("SceneManager");

	// リストの全要素を削除
	if (EnemyManager::IsListEmpty() == false)
	{
		EnemyManager::ClearEnemy();
	}

	Instantiate<Stage>(this);
	Instantiate<BattleWall>(this);
	Instantiate<WaterFloor>(this);
	Instantiate<BattleBackGround>(this);


	/*for (int i = 0; i < ENEMY_COUNT; i++)
	{
		EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	}*/

	pBoss = Instantiate<EnemyBoss>(this);
	pBoss->ProcessStart();

	//pBoss->SecondFormStart();

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

	// 敵がすべて倒されたら一定時間経過後、再登場する
	/*if (EnemyManager::IsListEmpty())
	{
		timer++;
		if (timer > EnemyTimer)
		{
			timer = 0;
			
			for (int i = 0; i < ENEMY_COUNT; i++)
			{
				EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
			}
		}		
	}*/

	//// 敵ボスキャラを登場させる処理
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
}

void DebugScene::Draw()
{
	
}

void DebugScene::Release()
{
}


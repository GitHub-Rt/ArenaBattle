#include "DebugScene.h"
#include "../Stage/Stage.h"

#include "../imgui/imguiObject.h"


#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"
#include "../Manager/EnemyManager.h"

#include "../Engine/Input.h"
#include "SceneManager.h"

// 定数宣言
const int EnemyTimer = 30;	// 敵が全滅してから再登場するまでのフレーム数

DebugScene::DebugScene(GameObject* parent)
	: GameObject(parent, "DebugScene")
{
	pBoss = nullptr;

}

void DebugScene::Initialize()
{
	

	Instantiate<Stage>(this);

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		//EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	}
	//pBoss = Instantiate<EnemyBoss>(this);
	
	pPlayer = Instantiate<Player>(this);
	Instantiate<Robot>(this);

	

	Instantiate<imguiObject>(this);
}

void DebugScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START)
#ifndef NDEBUG
		|| Input::IsKeyDown(DIK_ESCAPE)
#endif

		)
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
}

void DebugScene::Draw()
{

}

void DebugScene::Release()
{

}

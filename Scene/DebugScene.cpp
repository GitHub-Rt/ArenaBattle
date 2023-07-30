#include "DebugScene.h"
#include "../Stage/Stage.h"

#include "../imgui/imguiObject.h"


//#include "../Character/Player.h"
//#include "../Character/Robot.h"
//#include "../Character/Enemy.h"
//#include "../Character/EnemyBoss.h"
//#include "../Manager/EnemyManager.h"

#include "../UI/LevelSelectImage.h"
#include "../UI/SelectBox.h"

#include "../Engine/Input.h"
#include "SceneManager.h"

// 定数宣言
//const int EnemyTimer = 30;	// 敵が全滅してから再登場するまでのフレーム数
//const int ENEMY_COUNT = 3;

const float SELECT_BOX_POS_X = 0;
const float EASY_Y = -0.05f;
const float HARD_Y = -0.38f;

DebugScene::DebugScene(GameObject* parent)
	: GameObject(parent, "DebugScene")
{
	/*pBoss = nullptr;
	pPlayer = nullptr;
	timer = 0;*/

	pBox = nullptr;
}

void DebugScene::Initialize()
{
	/*Instantiate<Stage>(this);
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	}
	pBoss = Instantiate<EnemyBoss>(this);
	
	pPlayer = Instantiate<Player>(this);
	Instantiate<Robot>(this);*/
	
	Instantiate<LevelSelectImage>(this);
	pBox = Instantiate<SelectBox>(this);

	pBox->SetScale(XMFLOAT3(1, 1.3f, 1));
	pBox->SetSelectBox(XMFLOAT3(SELECT_BOX_POS_X, EASY_Y, 0));

	//Instantiate<imguiObject>(this);
}

void DebugScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) || Input::IsKeyDown(DIK_ESCAPE))
	{
		PostQuitMessage(0);	//プログラム終了
	}



	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || Input::IsKeyDown(DIK_DOWN))
	{
		pBox->SetSelectBox(XMFLOAT3(SELECT_BOX_POS_X, HARD_Y, 0));
	}

	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP) || Input::IsKeyDown(DIK_UP))
	{
		pBox->SetSelectBox(XMFLOAT3(SELECT_BOX_POS_X, EASY_Y, 0));
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
	//// ボス登場処理
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

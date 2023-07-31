#include "DebugScene.h"
#include "../Stage/Stage.h"

#include "../imgui/imguiObject.h"


#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"
#include "../Manager/EnemyManager.h"

#include "../UI/RetryImage.h"
#include "../UI/SelectBox.h";

#include "../Engine/Input.h"
#include "SceneManager.h"

// 定数宣言
const int EnemyTimer = 30;	// 敵が全滅してから再登場するまでのフレーム数
const int ENEMY_COUNT = 3;


DebugScene::DebugScene(GameObject* parent)
	: GameObject(parent, "DebugScene")
{
	pBoss = nullptr;
	pPlayer = nullptr;
	timer = 0;

	pManager = nullptr;

	pBox = nullptr;
	nowMenu = RetryMenu::Retry;
}

void DebugScene::Initialize()
{
	// HardModeに変更
	pManager = (SceneManager*)FindObject("SceneManager");
	pManager->SetHardModeFlg();


	Instantiate<Stage>(this);
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	}
	pBoss = Instantiate<EnemyBoss>(this);
	
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
	// ボス登場処理

	if (pBoss->IsEntered() == false && EnemyManager::IsListEmpty())
	{
		// プレイヤーの入力を受け付けなくする
		pPlayer->SetInputReception(false);
		if (pBoss->BossEntry())
		{
			// プレイヤーの入力受付を再開する
			pPlayer->SetInputReception(true);
			pBoss->ProcessStart();
		}
	}

	// Resultシーンへの移行処理
	{
		if (pPlayer->GetHP() <= 0)
		{
			// リトライするかどうかの確認の機能追加予定
			if (pBox == nullptr)
			{
				Instantiate<RetryImage>(this);
				pBox = Instantiate<SelectBox>(this);
			}

			// UI入力処理
			{
				if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP) || Input::IsKeyDown(DIK_UP))
				{
					nowMenu = RetryMenu::Retry;
				}

				if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || Input::IsKeyDown(DIK_DOWN))
				{
					nowMenu = RetryMenu::GameOver;
				}
			}
			
			// 選択
			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
			{
				switch (nowMenu)
				{
				case RetryMenu::Retry:
					BattleRetry();
					break;
				case RetryMenu::GameOver:
					pManager->ChangeScene(SCENE_ID::SCENE_ID_OVER);
					break;
				default:

					break;
				}
			}
			
		}

		if (pBoss->GetHP() <= 0)
		{
			pManager->ChangeScene(SCENE_ID::SCENE_ID_CLEAR);
		}
	}

}

void DebugScene::Draw()
{

}

void DebugScene::Release()
{

}


void DebugScene::BattleRetry()
{
	// 何か所かリスタートポイントを作成しておいてそれに応じて再スタートさせる処理を追加する
}
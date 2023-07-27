#include "BattleScene.h"
#include "SceneManager.h"

#include "../Stage/Stage.h"
#include "../Stage/BattleWall.h"
#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"
#include "../Manager/EnemyManager.h"


const int ENEMY_COUNT = 3;


BattleScene::BattleScene(GameObject* parent)
	: GameObject(parent, "BattleScene")
{
	pManager = nullptr;
	pBoss = nullptr;
	pPlayer = nullptr;
}

BattleScene::~BattleScene()
{

}

void BattleScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");

	Instantiate<Stage>(this);
	Instantiate<BattleWall>(this);

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	}
	pBoss = Instantiate<EnemyBoss>(this);

	pPlayer = Instantiate<Player>(this);
	Instantiate<Robot>(this);
}

void BattleScene::Update()
{
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
			pManager->ChangeScene(SCENE_ID::SCENE_ID_OVER);
		}

		if (pBoss->GetHP() <= 0)
		{
			pManager->ChangeScene(SCENE_ID::SCENE_ID_CLEAR);
		}
	}
	
}

void BattleScene::Draw()
{

}

void BattleScene::Release()
{

}
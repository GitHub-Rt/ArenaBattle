#include "BattleScene.h"
#include "SceneManager.h"
#include "../Sound/GameSound.h"

#include "../Stage/Stage.h"
#include "../Stage/BattleWall.h"
#include "../Stage/BattleBackGround.h"

#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"
#include "../Manager/EnemyManager.h"

#include "../UI/RetryImage.h"
#include "../UI/SelectBox.h";
#include "../Engine/Input.h"

const int ENEMY_COUNT = 3;


BattleScene::BattleScene(GameObject* parent)
	: GameObject(parent, "BattleScene")
{
	pManager = nullptr;
	pSound = nullptr;
	pBoss = nullptr;
	pPlayer = nullptr;

	pBox = nullptr;
	nowMenu = RetryMenu::Retry;
	isRetryProcess = false;
}

BattleScene::~BattleScene()
{

}

void BattleScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");
	pSound = pManager->GetSound();

	//pManager->SetHardModeFlg();

	pSound->SetSoundALLFalse();
	pSound->SoundLoad(SoundTrack::BattleSound);
	pSound->SoundLoad(SoundTrack::BossSound);
	pSound->SoundLoad(SoundTrack::LastBossSound);

	// リストの全要素を削除
	if (EnemyManager::IsListEmpty() == false)
	{
		EnemyManager::ClearEnemy();
	}

	Instantiate<Stage>(this);
	Instantiate<BattleWall>(this);
	//Instantiate<BattleBackGround>(this);

	// リトライポイントを取得する
	RetryPoint point = pManager->GetRetryPoint();

	// それぞれのリトライポイントに応じて再スタートする
	{
		// 通常Enemy戦から
		if (point == RetryPoint::NormalEnemyBattle)
		{
			for (int i = 0; i < ENEMY_COUNT; i++)
			{
				EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
			}
		}

		pBoss = Instantiate<EnemyBoss>(this);

		// 第二形態から
		if (point == RetryPoint::BossLastBattle)
		{
			pBoss->ProcessStart();
			pBoss->SecondFormStart();
		}

		pPlayer = Instantiate<Player>(this);
		Instantiate<Robot>(this);

	}

	// バトル音楽の再生
	
	switch (point)
	{
	case RetryPoint::NormalEnemyBattle:
		pSound->SoundPlay(SoundTrack::BattleSound);
		break;
	case RetryPoint::BossBattle:
		pSound->SoundPlay(SoundTrack::BossSound);
		break;
	case RetryPoint::BossLastBattle:
		pSound->SoundPlay(SoundTrack::LastBossSound);
		break;
	default:

		break;
	}
	
}

void BattleScene::Update()
{
	// ボス登場処理
	if (pBoss->IsEntered() == false && EnemyManager::IsListEmpty() && isRetryProcess == false)
	{
		// 音楽の変更
		if (pSound->GetSoundFlg(SoundTrack::BossSound) == false)
		{
			pSound->SoundStop(SoundTrack::BattleSound);
			pSound->SoundPlay(SoundTrack::BossSound);
		}

		// プレイヤーの入力を受け付けなくする
		pPlayer->SetInputReception(false);

		if (pBoss->BossEntry())
		{
			// プレイヤーの入力受付を再開する
			pPlayer->SetInputReception(true);
			pBoss->ProcessStart();

			// リトライポイントの更新
			pManager->SetRetryPoint(RetryPoint::BossBattle);
		}
	}

	// Resultシーンへの移行処理
	{
		if (pPlayer->GetHP() <= 0)
		{
			// UIの表示位置定数
			const float BOX_POS_X = -0.02f;
			const float RETORY_POS_Y = -0.06f;
			const float OVER_POS_Y = -0.425f;

			// リトライするかどうかの確認の機能追加予定
			if (pBox == nullptr)
			{
				Instantiate<RetryImage>(this);
				pBox = Instantiate<SelectBox>(this);
				pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, RETORY_POS_Y, 0));

				// ポーズ状態にする
				PoseProcess();
			}

			// UI入力処理
			{
				if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP) || Input::IsKeyDown(DIK_UP))
				{
					nowMenu = RetryMenu::Retry;
					pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, RETORY_POS_Y, 0));
				}

				if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || Input::IsKeyDown(DIK_DOWN))
				{
					nowMenu = RetryMenu::GameOver;
					pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, OVER_POS_Y, 0));
				}
			}

			// 選択
			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
			{
				isRetryProcess = false;

				switch (nowMenu)
				{
				case RetryMenu::Retry:
					BattleRetry();
					break;
				case RetryMenu::GameOver:
					pSound->SetSoundALLFalse();
					pManager->ChangeScene(SCENE_ID::SCENE_ID_OVER);
					break;
				default:

					break;
				}
			}
		}
		else if (pBoss->GetHP() <= 0)
		{
			pSound->SetSoundALLFalse();
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

void BattleScene::ChangeBossSound()
{
	pSound->SoundStop(SoundTrack::BossSound);
	pSound->SoundPlay(SoundTrack::LastBossSound);
}

void BattleScene::BattleRetry()
{
	// ボスのAIレベルが最大に達している(特殊攻撃を行った)かどうかを確認する
	if (pManager->GetRetryPoint() == RetryPoint::BossBattle && pBoss->GetAIState() == BossAIState::Caution)
	{
		pManager->SetRetryPoint(RetryPoint::BossLastBattle);
	}

	pManager->ReLoadScene(SCENE_ID::SCENE_ID_BATTLE);
}

void BattleScene::PoseProcess()
{
	isRetryProcess = true;

	if (EnemyManager::IsListEmpty() == false)
	{
		int nowEnemyCount = EnemyManager::GetVectorSize();

		for (int i = 0; i < nowEnemyCount; i++)
		{
			Enemy* pEnemy = EnemyManager::GetEnemyContent(i);
			pEnemy->Leave();
		}
	}

	pPlayer->SetInputReception(false);
	pBoss->Leave();
}
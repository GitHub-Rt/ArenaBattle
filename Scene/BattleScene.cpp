#include "BattleScene.h"
#include "SceneManager.h"
#include "../Sound/GameSound.h"

#include "../Stage/Stage.h"
#include "../Stage/BattleWall.h"
#include "../Stage/BattleBackGround.h"
#include "../Stage/WaterFloor.h"

#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"
#include "../Manager/EnemyManager.h"

#include "../UI/RetryImage.h"
#include "../UI/PauseImage.h"
#include "../UI/SelectBox.h";
#include "../UI/DefeatImage.h"
#include "../UI/VictoryImage.h"

#include "../Engine/Input.h"

const int ENEMY_COUNT = 3;

// UIの表示位置定数(PauseImage)
const float BOX_POS_X = -0.02f;
const float BACKGAME_POS_Y = -0.0125f;
const float START_POS_Y = -0.35f;

BattleScene::BattleScene(GameObject* parent)
	: GameObject(parent, "BattleScene")
{
	pManager = nullptr;
	pSound = nullptr;
	pBoss = nullptr;
	pPlayer = nullptr;

	pBox = nullptr;
	pPause = nullptr;
	nowRetryMenu = RetryMenu::Retry;
	nowMenu = Menu::BackGame;
	isRetryProcess = false;
	isPauseProcess = false;

	pDefeat = nullptr;
	pVictory = nullptr;
}

BattleScene::~BattleScene()
{

}

void BattleScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");
	pSound = pManager->GetSound();

	// サウンド、効果音のロード
	pSound->SetSoundALLFalse();
	pSound->SoundLoad(SoundTrack::TitleSound);
	pSound->SoundLoad(SoundTrack::BattleSound);
	pSound->SoundLoad(SoundTrack::Alert);
	pSound->SoundLoad(SoundTrack::BossSound);
	pSound->SoundLoad(SoundTrack::LastBossSound);
	pSound->EffectLoad(SoundEffect::Determinant);
	pSound->EffectLoad(SoundEffect::MoveSelection);

	// リストの全要素を削除
	if (EnemyManager::IsListEmpty() == false)
	{
		EnemyManager::ClearEnemy();
	}

	Instantiate<Stage>(this);
	Instantiate<BattleWall>(this);
	Instantiate<WaterFloor>(this);
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
		pSound->SoundPlay(SoundTrack::Alert);
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
	if (pBoss->IsEntered() == false && EnemyManager::IsListEmpty() && isRetryProcess == false && isPauseProcess == false)
	{
		// プレイヤーの入力を受け付けなくする
		pPlayer->SetInputReception(false);

		if (pBoss->BossEntry())
		{
			// 音楽の変更
			if (pSound->GetSoundFlg(SoundTrack::BossSound) == false)
			{
				pSound->SoundStop(SoundTrack::Alert);
				pSound->SoundPlay(SoundTrack::BossSound);
			}

			// プレイヤーの入力受付を再開する
			pPlayer->SetInputReception(true);
			pBoss->ProcessStart();

			// リトライポイントの更新
			pManager->SetRetryPoint(RetryPoint::BossBattle);
		}
		else
		{
			// Warningのアラート音を鳴らす
			if (pSound->GetSoundFlg(SoundTrack::BattleSound))
			{
				pSound->SoundStop(SoundTrack::BattleSound);
				pSound->SoundPlay(SoundTrack::Alert);
			}
		}
	}

	// 勝利、敗北画像表示中の処理
	if (pDefeat != nullptr || pVictory != nullptr)
	{
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
		{
			// 該当するリザルトシーンへ移行
			if (pVictory != nullptr)
			{
				pSound->SetSoundALLFalse();
				pManager->ChangeScene(SCENE_ID::SCENE_ID_CLEAR);
			}
			else
			{
				pSound->SetSoundALLFalse();
				pManager->SetRetryPoint(RetryPoint::NormalEnemyBattle);
				pManager->ChangeScene(SCENE_ID::SCENE_ID_OVER);
			}
		}
	}

	// 戦闘終了時処理
	{
		if (pPlayer->GetHP() <= 0)
		{
			const int MAX_CONTINUE = 3;	// 最大コンテニュー回数

			// まだコンテニュー可能かどうか
			if (pManager->GetContinueCount() < MAX_CONTINUE)
			{
				ContinueProcess();
			}
			else
			{
				pDefeat = Instantiate<DefeatImage>(this);
				PoseProcess();
			}
			
		}
		else if (pBoss->GetHP() <= 0)
		{
			pVictory = Instantiate<VictoryImage>(this);
			PoseProcess();
		}
	}
	
	// バトル中のメニュー処理
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) || Input::IsKeyDown(DIK_ESCAPE))
	{
		// メニュー画像呼び出し
		if (pBox == nullptr && pPause == nullptr)
		{
			pSound->SetSoundALLFalse();
			pSound->SoundPlay(SoundTrack::TitleSound);

			pPause = Instantiate<PauseImage>(this);
			pBox = Instantiate<SelectBox>(this);
			pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, BACKGAME_POS_Y, 0), true);

			PoseProcess();
			isPauseProcess = true;
		}
	}

	// ポーズ画像表示中の処理
	if (isPauseProcess)
	{
		// UI入力処理
		{
			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP) || Input::IsKeyDown(DIK_UP))
			{
				if (pSound->GetEffectFlg(SoundEffect::MoveSelection))
				{
					pSound->EffectStop(SoundEffect::MoveSelection);
				}
				pSound->EffectPlay(SoundEffect::MoveSelection);
				nowMenu = Menu::BackGame;
				pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, BACKGAME_POS_Y, 0), true);
			}

			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || Input::IsKeyDown(DIK_DOWN))
			{
				pSound->EffectPlay(SoundEffect::MoveSelection);
				nowMenu = Menu::ToStart;
				pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, START_POS_Y, 0));
			}
		}

		// 選択
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
		{
			pSound->EffectPlay(SoundEffect::Determinant);

			isPauseProcess = false;

			switch (nowMenu)
			{
			case Menu::BackGame:
				BackBattle();
				break;
			case Menu::ToStart:
				pSound->SetSoundALLFalse();
				pManager->SetRetryPoint(RetryPoint::NormalEnemyBattle);
				pManager->ChangeScene(SCENE_ID::SCENE_ID_START);
				break;
			default:
				break;
			}
		}
	}
	else
	{
		pPlayer->SetInputReception(true);
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
	// コンテニュー回数を加算
	pManager->ContinueCountIncrease();

	// ボスのAIレベルが最大に達している(特殊攻撃を行った)かどうかを確認する
	if (pManager->GetRetryPoint() == RetryPoint::BossBattle && pBoss->GetAIState() == BossAIState::Caution)
	{
		pManager->SetRetryPoint(RetryPoint::BossLastBattle);
	}

	pManager->ReLoadScene(SCENE_ID::SCENE_ID_BATTLE);
}

void BattleScene::BackBattle()
{
	RetryPoint point = pManager->GetRetryPoint();

	pSound->SoundStop(SoundTrack::TitleSound);

	// サウンドの再生
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

	// オブジェクトの更新を再開
	if (EnemyManager::IsListEmpty() == false)
	{
		int nowEnemyCount = EnemyManager::GetVectorSize();

		for (int i = 0; i < nowEnemyCount; i++)
		{
			Enemy* pEnemy = EnemyManager::GetEnemyContent(i);
			pEnemy->Enter();
		}
	}

	if (point != RetryPoint::NormalEnemyBattle)
	{
		pBoss->Enter();
	}

	// 変数のリセット
	pBox->KillMe();
	pBox = nullptr;
	pPause->KillMe();
	pPause = nullptr;
}

void BattleScene::PoseProcess()
{
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

void BattleScene::ContinueProcess()
{
	// UIの表示位置定数
	const float BOX_POS_X = -0.02f;
	const float RETORY_POS_Y = -0.06f;
	const float OVER_POS_Y = -0.425f;

	// リトライするかどうかの選択をさせるオブジェクトを呼び出す
	if (pBox == nullptr)
	{
		Instantiate<RetryImage>(this);
		pBox = Instantiate<SelectBox>(this);
		pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, RETORY_POS_Y, 0));

		// ポーズ状態にする
		PoseProcess();
		isRetryProcess = true;
	}

	// UI入力処理
	{
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP) || Input::IsKeyDown(DIK_UP))
		{
			pSound->EffectPlay(SoundEffect::MoveSelection);
			nowRetryMenu = RetryMenu::Retry;
			pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, RETORY_POS_Y, 0));
		}

		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || Input::IsKeyDown(DIK_DOWN))
		{
			pSound->EffectPlay(SoundEffect::MoveSelection);
			nowRetryMenu = RetryMenu::GameOver;
			pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, OVER_POS_Y, 0));
		}
	}

	// 選択
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
	{
		pSound->EffectPlay(SoundEffect::Determinant);

		isRetryProcess = false;

		switch (nowRetryMenu)
		{
		case RetryMenu::Retry:
			BattleRetry();
			break;
		case RetryMenu::GameOver:
			pSound->SetSoundALLFalse();
			pManager->SetRetryPoint(RetryPoint::NormalEnemyBattle);
			pManager->ChangeScene(SCENE_ID::SCENE_ID_OVER);
			break;
		default:
			break;
		}
	}
}
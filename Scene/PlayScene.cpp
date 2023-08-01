#include "PlayScene.h"
#include "SceneManager.h"
#include "../Sound/GameSound.h"
#include "../Engine/Input.h"

#include "../Stage/NormalField.h"
#include "../Stage/Wall.h"
#include "../Stage/BattleStartCylinder.h"
#include "../Character/Player.h"
#include "../Character/Robot.h"

#include "../UI/LevelSelectImage.h"
#include "../UI/SelectBox.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
	pManager = nullptr;
	pSound = nullptr;
	pBox = nullptr;
	pPlayer = nullptr;
	nowLevel = GameLevel::Easy;
}

PlayScene::~PlayScene()
{

}

void PlayScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");
	pSound = pManager->GetSound();

	if (pManager->GetPrevScene() == SCENE_ID::SCENE_ID_RELEASE)
	{
		pSound->SoundStop(SoundTrack::TitleSound);
	}

	pSound->SoundLoad(SoundTrack::PlaySceneSound);

	Instantiate<NormalField>(this);
	Instantiate<Wall>(this);
	Instantiate<BattleStartCylinder>(this);
	pPlayer = Instantiate<Player>(this);
	Instantiate<Robot>(this);

	
	pSound->SoundPlay(SoundTrack::PlaySceneSound);
}

void PlayScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) || Input::IsKeyDown(DIK_ESCAPE))
	{
		pManager->ChangeScene(SCENE_ID::SCENE_ID_RELEASE);
	}
}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{

}

void PlayScene::BattleStart()
{
	// 二周目かどうかを調べて該当していたら画像で難易度選択を行わせる予定
	if (pManager->GetClearFlg())
	{
		const float SELECT_BOX_POS_X = 0;
		const float EASY_Y = -0.05f;
		const float HARD_Y = -0.38f;

		// レベル選択画像を表示させる
		if (pBox == nullptr)
		{
			const XMFLOAT3 BOX_SCALE = XMFLOAT3(1, 1.3f, 1);

			// プレイヤーの入力を受け付けなくする
			pPlayer->SetInputReception(false);

			Instantiate<LevelSelectImage>(this);
			pBox = Instantiate<SelectBox>(this);
			pBox->SetScale(BOX_SCALE);
			pBox->SetSelectBox(XMFLOAT3(SELECT_BOX_POS_X, EASY_Y, 0));
		}
		
		// レベル選択入力
		{
			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP) || Input::IsKeyDown(DIK_UP))
			{
				pBox->SetSelectBox(XMFLOAT3(SELECT_BOX_POS_X, EASY_Y, 0));
				nowLevel = GameLevel::Easy;
			}

			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || Input::IsKeyDown(DIK_DOWN))
			{
				pBox->SetSelectBox(XMFLOAT3(SELECT_BOX_POS_X, HARD_Y, 0));
				nowLevel = GameLevel::Hard;
			}
		}
		
		// レベル決定
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
		{
			pManager->SetHardModeFlg();
			pSound->SoundStop(SoundTrack::PlaySceneSound);
			pManager->ChangeScene(SCENE_ID::SCENE_ID_BATTLE);
		}
		
	}
	else
	{
		pSound->SoundStop(SoundTrack::PlaySceneSound);
		pManager->ChangeScene(SCENE_ID::SCENE_ID_BATTLE);
	}
}
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
	Instantiate<Player>(this);
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
	// “ñŽü–Ú‚©‚Ç‚¤‚©‚ð’²‚×‚ÄŠY“–‚µ‚Ä‚¢‚½‚ç‰æ‘œ‚Å“ïˆÕ“x‘I‘ð‚ðs‚í‚¹‚é—\’è
	if (pManager->GetClearFlg())
	{
		Instantiate<LevelSelectImage>(this);
		pBox = Instantiate<SelectBox>(this);


	}
	else
	{
		pSound->SoundStop(SoundTrack::PlaySceneSound);
		pManager->ChangeScene(SCENE_ID::SCENE_ID_BATTLE);
	}
}
#include "HowToPlayScene.h"

#include "SceneManager.h"
#include "../Sound/GameSound.h"

#include "../Engine/Input.h"

#include "../UI/HowToPlayImage.h"

HowToPlayScene::HowToPlayScene(GameObject* parent)
	: GameObject(parent, "HowToPlayScene")
{
	pManager = nullptr;
	pSound = nullptr;
}

HowToPlayScene::~HowToPlayScene()
{

}

void HowToPlayScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");
	pSound = pManager->GetSound();

	Instantiate<HowToPlayImage>(this);
}

void HowToPlayScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
	{
		pSound->SoundStop(SoundTrack::TitleSound);
		pManager->ChangeScene(SCENE_ID::SCENE_ID_PLAY);
	}
}

void HowToPlayScene::Draw()
{

}

void HowToPlayScene::Release()
{

}
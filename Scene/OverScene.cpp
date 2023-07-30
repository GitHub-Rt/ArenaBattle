#include "OverScene.h"
#include "SceneManager.h"
#include "../Sound/GameSound.h"
#include "../Engine/Input.h"

#include "../UI/BackGroundImage.h"
#include "../UI/OverImage.h"

OverScene::OverScene(GameObject* parent)
	: GameObject(parent, "OverScene")
{
	pManager = nullptr;
	pSound = nullptr;
}

OverScene::~OverScene()
{

}

void OverScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");
	pSound = pManager->GetSound();
	pSound->SoundLoad(SoundTrack::GameOverSound);

	Instantiate<BackGroundImage>(this);
	Instantiate<OverImage>(this);

	pSound->SoundPlay(SoundTrack::GameOverSound);
}

void OverScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
	{
		pSound->SoundStop(SoundTrack::GameOverSound);
		pManager->ChangeScene(SCENE_ID::SCENE_ID_TITLE);
	}
}

void OverScene::Draw()
{

}

void OverScene::Release()
{

}
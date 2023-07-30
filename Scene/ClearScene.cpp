#include "ClearScene.h"
#include "SceneManager.h"
#include "../Sound/GameSound.h"

#include "../Engine/Input.h"

#include "../UI/BackGroundImage.h"
#include "../UI/ClearImage.h"

ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene")
{
	pManager = nullptr;
	pSound = nullptr;
}

ClearScene::~ClearScene()
{

}

void ClearScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");
	pSound = pManager->GetSound();

	pSound->SoundLoad(SoundTrack::ClearSound);

	Instantiate<BackGroundImage>(this);
	Instantiate<ClearImage>(this);

	pSound->SoundPlay(SoundTrack::ClearSound);
}

void ClearScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
	{
		pSound->SoundStop(SoundTrack::ClearSound);
		pManager->ChangeScene(SCENE_ID::SCENE_ID_TITLE);
	}
}

void ClearScene::Draw()
{

}

void ClearScene::Release()
{

}

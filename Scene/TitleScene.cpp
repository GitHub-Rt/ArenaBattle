#include "TitleScene.h"

#include "SceneManager.h"
#include "../UI/BackGroundImage.h"
#include "../UI/TitleImage.h"
#include "../Sound/GameSound.h"

#include "../Engine/Input.h"

TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
	pManager = nullptr;
	pSound = nullptr;
	pImage = nullptr;
}

void TitleScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");
	pSound = pManager->GetSound();
	
	pSound->SoundLoad(SoundTrack::TitleSound);
	pSound->EffectLoad(SoundEffect::Determinant);
	
	Instantiate<BackGroundImage>(this);
	pImage = Instantiate<TitleImage>(this);

	pSound->SoundPlay(SoundTrack::TitleSound);
}

void TitleScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) || Input::IsKeyDown(DIK_ESCAPE))
	{
		pManager->ChangeScene(SCENE_ID::SCENE_ID_RELEASE);
	}

	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
	{
		pSound->EffectPlay(SoundEffect::Determinant);

		// まだタイトル画像が不透明じゃない状態だったら不透明にする
		if (pImage->GetAlpha() != 1)
		{
			pImage->SetMaxAlpha();
		}
		else
		{
			pManager->ChangeScene(SCENE_ID::SCENE_ID_START);
		}
	}


}

void TitleScene::Draw()
{
}

void TitleScene::Release()
{
}
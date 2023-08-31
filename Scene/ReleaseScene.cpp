#include "ReleaseScene.h"

#include "SceneManager.h"
#include "../Sound/GameSound.h"
#include "../UI/BackGroundImage.h"
#include "../UI/ReleaseImage.h"
#include "../UI/SelectBox.h"

#include "../Engine/Input.h"

const float POS_X = -0.0375f;
const float RELEASE_BACK_POS_X = -0.0225f;
const float RELEASE_BACK_Y = 0.0125f;
const float RELEASE_END_Y = -0.35f;

ReleaseScene::ReleaseScene(GameObject* parent)
	: GameObject(parent, "ReleaseScene")
{
	pManager = nullptr;
	pSound = nullptr;
	pBox = nullptr;
	nowState = ReleaseState::BackGame;
}

ReleaseScene::~ReleaseScene()
{

}

void ReleaseScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");
	pSound = pManager->GetSound();


	if (pManager->GetPrevScene() == SCENE_ID::SCENE_ID_PLAY)
	{
		pSound->SoundLoad(SoundTrack::TitleSound);
		pSound->SoundStop(SoundTrack::PlaySceneSound);
		pSound->SoundPlay(SoundTrack::TitleSound);
	}

	pSound->EffectLoad(SoundEffect::Determinant);
	pSound->EffectLoad(SoundEffect::MoveSelection);

	Instantiate<BackGroundImage>(this);
	Instantiate<ReleaseImage>(this);
	pBox = Instantiate<SelectBox>(this);
	pBox->SetSelectBox(XMFLOAT3(RELEASE_BACK_POS_X, RELEASE_BACK_Y, 0), true);
}

void ReleaseScene::Update()
{
	// �J�ڐ�V�[���̑I��؂�ւ�(UI�\���ʒu�̕ύX)
	ChangeStateUIPosition();

	// �Y������V�[���ɑJ�ڂ���
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
	{
		if (pSound->GetEffectFlg(SoundEffect::Determinant))
		{
			pSound->EffectStop(SoundEffect::Determinant);
		}
		pSound->EffectPlay(SoundEffect::Determinant);

		switch (nowState)
		{
		case ReleaseState::BackGame:
			pManager->ChangeScene((SCENE_ID)pManager->GetPrevScene());
			break;
		case ReleaseState::ExitGame:
			PostQuitMessage(0);	//�v���O�����I��
			break;
		default:
			break;
		}
		
	}



}

void ReleaseScene::Draw()
{

}

void ReleaseScene::Release()
{

}

void ReleaseScene::ChangeStateUIPosition()
{
	// �ڍs�O�̏�Ԃ�ۑ�
	ReleaseState prevState = nowState;

	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || Input::IsKeyDown(DIK_DOWN))
	{
		if (pSound->GetEffectFlg(SoundEffect::MoveSelection))
		{
			pSound->EffectStop(SoundEffect::MoveSelection);
		}
		pSound->EffectPlay(SoundEffect::MoveSelection);


		// ��ԉ��̍��ڂ����̏�Ԃł͂Ȃ������m�F
		if (nowState != ReleaseState::ExitGame)
		{
			// ���̗v�f�Ɉڍs
			int now = (int)nowState;
			now++;
			nowState = (ReleaseState)now;
		}
	}
	else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP) || Input::IsKeyDown(DIK_UP))
	{
		if (pSound->GetEffectFlg(SoundEffect::MoveSelection))
		{
			pSound->EffectStop(SoundEffect::MoveSelection);
		}
		pSound->EffectPlay(SoundEffect::MoveSelection);

		// ��ԏ�̍��ڂ����̏�Ԃł͂Ȃ������m�F
		if (nowState != ReleaseState::BackGame)
		{
			// 1�O�̗v�f�Ɉڍs
			int now = (int)nowState;
			now--;
			nowState = (ReleaseState)now;
		}
	}


	// �v�f�̈ڍs������ꂽ�� �Y���v�f�̈ʒu��UI���Z�b�g
	if (prevState != nowState)
	{
		switch (nowState)
		{
		case ReleaseState::BackGame:
			pBox->SetSelectBox(XMFLOAT3(RELEASE_BACK_POS_X, RELEASE_BACK_Y, 0), true);
			break;
		case ReleaseState::ExitGame:
			pBox->SetSelectBox(XMFLOAT3(POS_X, RELEASE_END_Y, 0));
			break;
		default:
			break;
		}
	}
}
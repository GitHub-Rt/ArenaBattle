#include "StartScene.h"

#include "SceneManager.h"
#include "../Sound/GameSound.h"
#include "../UI/BackGroundImage.h"
#include "../UI/StartImage.h"
#include "../UI/SelectBox.h"

#include "../Engine/Input.h"

const float SELECT_BOX_POS_X = -0.0375f;
const float START_PLAY_Y = 0.22f;
const float START_CONTROLLER_Y = -0.38f;
const float START_KEYBOARD_Y = -0.615f;



StartScene::StartScene(GameObject* parent)
	: GameObject(parent, "StartScene")
{
	pManager = nullptr;
	pSound = nullptr;
	pBox = nullptr;
	nowState = StartState::GameStart;
}

StartScene::~StartScene()
{

}

void StartScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");
	pSound = pManager->GetSound();

	pManager->ContinueCountReset();

	pSound->EffectLoad(SoundEffect::Determinant);
	pSound->EffectLoad(SoundEffect::MoveSelection);

	Instantiate<BackGroundImage>(this);
	Instantiate<StartImage>(this);
	pBox = Instantiate<SelectBox>(this);
	pBox->SetSelectBox(XMFLOAT3(SELECT_BOX_POS_X, START_PLAY_Y, 0));
}

void StartScene::Update()
{
	// �J�ڐ�V�[���̑I��؂�ւ�(UI�\���ʒu�̕ύX)
	ChangeStateUIPosition();

	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) || Input::IsKeyDown(DIK_ESCAPE))
	{
		pManager->ChangeScene(SCENE_ID::SCENE_ID_TITLE);
	}

	// �Y������V�[���ɑJ�ڂ���
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
	{
		pSound->EffectPlay(SoundEffect::Determinant);

		switch (nowState)
		{
		case StartState::GameStart:
			pSound->SoundStop(SoundTrack::TitleSound);
			pManager->ChangeScene(SCENE_ID::SCENE_ID_PLAY);
			break;
		case StartState::Controller:
			pManager->ChangeScene(SCENE_ID::SCENE_ID_CONTROLLEROPERATION);
			break;
		case StartState::Keyboard:
			pManager->ChangeScene(SCENE_ID::SCENE_ID_KEYBOARDOPERATION);
			break;
		default:
			break;
		}
	}
}

void StartScene::Draw()
{

}

void StartScene::Release()
{

}

void StartScene::ChangeStateUIPosition()
{
	// �ڍs�O�̗v�f��ۑ�
	StartState prevState = nowState;


	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || Input::IsKeyDown(DIK_DOWN))
	{
		pSound->EffectPlay(SoundEffect::MoveSelection);

		// ��ԉ��̍��ڂ����̏�Ԃł͂Ȃ������m�F
		if (nowState != StartState::Keyboard)
		{
			// ���̗v�f�Ɉڍs
			int now = (int)nowState;
			now++;
			nowState = (StartState)now;
		}
	}
	else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP) || Input::IsKeyDown(DIK_UP))
	{
		pSound->EffectPlay(SoundEffect::MoveSelection);

		// ��ԏ�̍��ڂ����̏�Ԃł͂Ȃ������m�F
		if (nowState != StartState::GameStart)
		{
			// 1�O�̗v�f�Ɉڍs
			int now = (int)nowState;
			now--;
			nowState = (StartState)now;
		}
	}


	// �v�f�̈ڍs������ꂽ�� �Y���v�f�̈ʒu��UI���Z�b�g
	if (prevState != nowState)
	{
		switch (nowState)
		{
		case StartState::GameStart:
			pBox->SetSelectBox(XMFLOAT3(SELECT_BOX_POS_X, START_PLAY_Y, 0));
			break;
		case StartState::Controller:
			pBox->SetSelectBox(XMFLOAT3(SELECT_BOX_POS_X, START_CONTROLLER_Y, 0));
			break;
		case StartState::Keyboard:
			pBox->SetSelectBox(XMFLOAT3(SELECT_BOX_POS_X, START_KEYBOARD_Y, 0));
			break;
		default:
			break;
		}
	}
	
}
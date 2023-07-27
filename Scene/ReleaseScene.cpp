#include "ReleaseScene.h"

#include "SceneManager.h"
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
	pBox = nullptr;
	nowState = ReleaseState::BackGame;
}

ReleaseScene::~ReleaseScene()
{

}

void ReleaseScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");

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
#include "DebugScene.h"
#include "../Stage/Stage.h"

#include "../imgui/imguiObject.h"


//#include "../Character/Player.h"
//#include "../Character/Robot.h"
//#include "../Character/Enemy.h"
//#include "../Character/EnemyBoss.h"
//#include "../Manager/EnemyManager.h"

#include "../UI/LevelSelectImage.h"
#include "../UI/SelectBox.h"

#include "../Engine/Input.h"
#include "SceneManager.h"

// �萔�錾
//const int EnemyTimer = 30;	// �G���S�ł��Ă���ēo�ꂷ��܂ł̃t���[����
//const int ENEMY_COUNT = 3;

const float SELECT_BOX_POS_X = 0;
const float EASY_Y = -0.05f;
const float HARD_Y = -0.38f;

DebugScene::DebugScene(GameObject* parent)
	: GameObject(parent, "DebugScene")
{
	/*pBoss = nullptr;
	pPlayer = nullptr;
	timer = 0;*/

	pBox = nullptr;
}

void DebugScene::Initialize()
{
	/*Instantiate<Stage>(this);
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	}
	pBoss = Instantiate<EnemyBoss>(this);
	
	pPlayer = Instantiate<Player>(this);
	Instantiate<Robot>(this);*/
	
	Instantiate<LevelSelectImage>(this);
	pBox = Instantiate<SelectBox>(this);

	pBox->SetScale(XMFLOAT3(1, 1.3f, 1));
	pBox->SetSelectBox(XMFLOAT3(SELECT_BOX_POS_X, EASY_Y, 0));

	//Instantiate<imguiObject>(this);
}

void DebugScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) || Input::IsKeyDown(DIK_ESCAPE))
	{
		PostQuitMessage(0);	//�v���O�����I��
	}



	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || Input::IsKeyDown(DIK_DOWN))
	{
		pBox->SetSelectBox(XMFLOAT3(SELECT_BOX_POS_X, HARD_Y, 0));
	}

	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP) || Input::IsKeyDown(DIK_UP))
	{
		pBox->SetSelectBox(XMFLOAT3(SELECT_BOX_POS_X, EASY_Y, 0));
	}

	//// �G�����ׂē|���ꂽ���莞�Ԍo�ߌ�A�ēo�ꂷ��
	//if (EnemyManager::IsListEmpty())
	//{
	//	timer++;
	//	if (timer > EnemyTimer)
	//	{
	//		timer = 0;
	//		
	//		for (int i = 0; i < ENEMY_COUNT; i++)
	//		{
	//			EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	//		}
	//	}		
	//}
	//// �{�X�o�ꏈ��
	//if (pBoss->IsEntered() == false && EnemyManager::IsListEmpty())
	//{
	//	// �v���C���[�̓��͂��󂯕t���Ȃ�����
	//	pPlayer->SetInputReception(false);
	//	if (pBoss->BossEntry())
	//	{
	//		// �v���C���[�̓��͎�t���ĊJ����
	//		pPlayer->SetInputReception(true);
	//		pBoss->ProcessStart();
	//	}
	//}
}

void DebugScene::Draw()
{

}

void DebugScene::Release()
{

}

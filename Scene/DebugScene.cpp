#include "DebugScene.h"
#include "../Stage/Stage.h"

#include "../imgui/imguiObject.h"


#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"
#include "../Manager/EnemyManager.h"

#include "../UI/RetryImage.h"
#include "../UI/SelectBox.h";

#include "../Engine/Input.h"
#include "SceneManager.h"

// �萔�錾
const int EnemyTimer = 30;	// �G���S�ł��Ă���ēo�ꂷ��܂ł̃t���[����
const int ENEMY_COUNT = 3;


DebugScene::DebugScene(GameObject* parent)
	: GameObject(parent, "DebugScene")
{
	pBoss = nullptr;
	pPlayer = nullptr;
	timer = 0;

	pManager = nullptr;

	pBox = nullptr;
	nowMenu = RetryMenu::Retry;
}

void DebugScene::Initialize()
{
	// HardMode�ɕύX
	pManager = (SceneManager*)FindObject("SceneManager");
	pManager->SetHardModeFlg();


	Instantiate<Stage>(this);
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	}
	pBoss = Instantiate<EnemyBoss>(this);
	
	pPlayer = Instantiate<Player>(this);
	Instantiate<Robot>(this);

	Instantiate<imguiObject>(this);
}

void DebugScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) || Input::IsKeyDown(DIK_ESCAPE))
	{
		PostQuitMessage(0);	//�v���O�����I��
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
	// �{�X�o�ꏈ��

	if (pBoss->IsEntered() == false && EnemyManager::IsListEmpty())
	{
		// �v���C���[�̓��͂��󂯕t���Ȃ�����
		pPlayer->SetInputReception(false);
		if (pBoss->BossEntry())
		{
			// �v���C���[�̓��͎�t���ĊJ����
			pPlayer->SetInputReception(true);
			pBoss->ProcessStart();
		}
	}

	// Result�V�[���ւ̈ڍs����
	{
		if (pPlayer->GetHP() <= 0)
		{
			// ���g���C���邩�ǂ����̊m�F�̋@�\�ǉ��\��
			if (pBox == nullptr)
			{
				Instantiate<RetryImage>(this);
				pBox = Instantiate<SelectBox>(this);
			}

			// UI���͏���
			{
				if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP) || Input::IsKeyDown(DIK_UP))
				{
					nowMenu = RetryMenu::Retry;
				}

				if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || Input::IsKeyDown(DIK_DOWN))
				{
					nowMenu = RetryMenu::GameOver;
				}
			}
			
			// �I��
			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
			{
				switch (nowMenu)
				{
				case RetryMenu::Retry:
					BattleRetry();
					break;
				case RetryMenu::GameOver:
					pManager->ChangeScene(SCENE_ID::SCENE_ID_OVER);
					break;
				default:

					break;
				}
			}
			
		}

		if (pBoss->GetHP() <= 0)
		{
			pManager->ChangeScene(SCENE_ID::SCENE_ID_CLEAR);
		}
	}

}

void DebugScene::Draw()
{

}

void DebugScene::Release()
{

}


void DebugScene::BattleRetry()
{
	// �����������X�^�[�g�|�C���g���쐬���Ă����Ă���ɉ����čăX�^�[�g�����鏈����ǉ�����
}
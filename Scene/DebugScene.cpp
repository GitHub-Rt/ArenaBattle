#include "DebugScene.h"
#include "../Stage/Stage.h"

#include "../imgui/imguiObject.h"


#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"
#include "../Manager/EnemyManager.h"

#include "../Engine/Input.h"
#include "SceneManager.h"

// �萔�錾
const int EnemyTimer = 30;	// �G���S�ł��Ă���ēo�ꂷ��܂ł̃t���[����

DebugScene::DebugScene(GameObject* parent)
	: GameObject(parent, "DebugScene")
{
	pBoss = nullptr;

}

void DebugScene::Initialize()
{
	

	Instantiate<Stage>(this);

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		//EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	}
	//pBoss = Instantiate<EnemyBoss>(this);
	
	pPlayer = Instantiate<Player>(this);
	Instantiate<Robot>(this);

	

	Instantiate<imguiObject>(this);
}

void DebugScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START)
#ifndef NDEBUG
		|| Input::IsKeyDown(DIK_ESCAPE)
#endif

		)
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

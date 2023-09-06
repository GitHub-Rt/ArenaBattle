#include "DebugScene.h"
#include "../Stage/Stage.h"

#include "../imgui/imguiObject.h"
#include "../Stage/BattleBackGround.h"
#include "../Stage/BattleWall.h"

#include "../Stage/WaterFloor.h"

#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"
#include "../Manager/EnemyManager.h"

#include "../Scene/SceneManager.h"
#include "../Engine/Input.h"
#include "../Effect/Effect.h"

// �萔�錾
const int EnemyTimer = 30;	// �G���S�ł��Ă���ēo�ꂷ��܂ł̃t���[����
const int ENEMY_COUNT = 3;


DebugScene::DebugScene(GameObject* parent)
	: GameObject(parent, "DebugScene")
{
	pPlayer = nullptr;
	pBoss = nullptr;
	timer = 0;
}

void DebugScene::Initialize()
{
	if (EnemyManager::IsListEmpty() == false)
	{
		EnemyManager::ClearEnemy();
	}
	
	Instantiate<Stage>(this);
	Instantiate<BattleWall>(this);
	//Instantiate<BattleBackGround>(this);
	Instantiate<WaterFloor>(this);

	//for (int i = 0; i < ENEMY_COUNT; i++)
	//{
	//	EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	//}

	//pBoss = Instantiate<EnemyBoss>(this);
	// �{�X������n�߂�
	//pBoss->ProcessStart();

	// ���`�Ԃ���X�^�[�g������
	///pBoss->SecondFormStart();
	
	pPlayer = Instantiate<Player>(this);
	Instantiate<Robot>(this);

	Instantiate<imguiObject>(this);

	pEffect = new Effect();
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

	//// �G�{�X�L������o�ꂳ���鏈��
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

	if (Input::IsKey(DIK_SPACE))
	{
		pEffect->SetEmitterPosition(XMFLOAT3(0,0,0), EmitterType::Dead);
		pEffect->StartEffectDead();
	}
	
	
}

void DebugScene::Draw()
{
	
}

void DebugScene::Release()
{
	if (pEffect != nullptr)
	{
		pEffect->Release();
		SAFE_DELETE(pEffect);
	}
}


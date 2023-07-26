#include "BattleScene.h"
#include "SceneManager.h"

#include "../Stage/Stage.h"
#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"
#include "../Manager/EnemyManager.h"


const int ENEMY_COUNT = 3;


BattleScene::BattleScene(GameObject* parent)
	: GameObject(parent, "BattleScene")
{
	pManager = nullptr;
	pBoss = nullptr;
	pPlayer = nullptr;
}

BattleScene::~BattleScene()
{

}

void BattleScene::Initialize()
{
	Instantiate<Stage>(this);

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	}
	pBoss = Instantiate<EnemyBoss>(this);

	pPlayer = Instantiate<Player>(this);
	Instantiate<Robot>(this);
}

void BattleScene::Update()
{
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
}

void BattleScene::Draw()
{

}

void BattleScene::Release()
{

}
#include "BattleScene.h"
#include "SceneManager.h"
#include "../Sound/GameSound.h"

#include "../Stage/Stage.h"
#include "../Stage/BattleWall.h"
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
	pSound = nullptr;
	pBoss = nullptr;
	pPlayer = nullptr;
}

BattleScene::~BattleScene()
{

}

void BattleScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");
	pSound = pManager->GetSound();

	pSound->SoundLoad(SoundTrack::BattleSound);
	pSound->SoundLoad(SoundTrack::BossSound);
	pSound->SoundLoad(SoundTrack::LastBossSound);

	Instantiate<Stage>(this);
	Instantiate<BattleWall>(this);

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	}
	pBoss = Instantiate<EnemyBoss>(this);

	pPlayer = Instantiate<Player>(this);
	Instantiate<Robot>(this);

	pSound->SoundPlay(SoundTrack::BattleSound);
}

void BattleScene::Update()
{
	// �{�X�o�ꏈ��
	if (pBoss->IsEntered() == false && EnemyManager::IsListEmpty())
	{
		// ���y�̕ύX
		if (pSound->GetSoundFlg(SoundTrack::BossSound) == false)
		{
			pSound->SoundStop(SoundTrack::BattleSound);
			pSound->SoundPlay(SoundTrack::BossSound);
		}

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
			pSound->SetSoundALLFalse();
			pManager->ChangeScene(SCENE_ID::SCENE_ID_OVER);
		}

		if (pBoss->GetHP() <= 0)
		{
			pSound->SetSoundALLFalse();
			pManager->ChangeScene(SCENE_ID::SCENE_ID_CLEAR);
		}
	}
	
}

void BattleScene::Draw()
{

}

void BattleScene::Release()
{

}

void BattleScene::ChangeBossSound()
{
	pSound->SoundStop(SoundTrack::BossSound);
	pSound->SoundPlay(SoundTrack::LastBossSound);
}
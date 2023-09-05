#include "BattleScene.h"
#include "SceneManager.h"
#include "../Sound/GameSound.h"

#include "../Stage/Stage.h"
#include "../Stage/BattleWall.h"
#include "../Stage/BattleBackGround.h"
#include "../Stage/WaterFloor.h"

#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"
#include "../Manager/EnemyManager.h"

#include "../UI/RetryImage.h"
#include "../UI/PauseImage.h"
#include "../UI/SelectBox.h";
#include "../UI/DefeatImage.h"
#include "../UI/VictoryImage.h"

#include "../Engine/Input.h"

const int ENEMY_COUNT = 3;

// UI�̕\���ʒu�萔(PauseImage)
const float BOX_POS_X = -0.02f;
const float BACKGAME_POS_Y = -0.0125f;
const float START_POS_Y = -0.35f;

BattleScene::BattleScene(GameObject* parent)
	: GameObject(parent, "BattleScene")
{
	pManager = nullptr;
	pSound = nullptr;
	pBoss = nullptr;
	pPlayer = nullptr;

	pBox = nullptr;
	pPause = nullptr;
	nowRetryMenu = RetryMenu::Retry;
	nowMenu = Menu::BackGame;
	isRetryProcess = false;
	isPauseProcess = false;

	pDefeat = nullptr;
	pVictory = nullptr;
}

BattleScene::~BattleScene()
{

}

void BattleScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");
	pSound = pManager->GetSound();

	// �T�E���h�A���ʉ��̃��[�h
	pSound->SetSoundALLFalse();
	pSound->SoundLoad(SoundTrack::TitleSound);
	pSound->SoundLoad(SoundTrack::BattleSound);
	pSound->SoundLoad(SoundTrack::Alert);
	pSound->SoundLoad(SoundTrack::BossSound);
	pSound->SoundLoad(SoundTrack::LastBossSound);
	pSound->EffectLoad(SoundEffect::Determinant);
	pSound->EffectLoad(SoundEffect::MoveSelection);

	// ���X�g�̑S�v�f���폜
	if (EnemyManager::IsListEmpty() == false)
	{
		EnemyManager::ClearEnemy();
	}

	Instantiate<Stage>(this);
	Instantiate<BattleWall>(this);
	Instantiate<WaterFloor>(this);
	//Instantiate<BattleBackGround>(this);

	// ���g���C�|�C���g���擾����
	RetryPoint point = pManager->GetRetryPoint();

	// ���ꂼ��̃��g���C�|�C���g�ɉ����čăX�^�[�g����
	{
		// �ʏ�Enemy�킩��
		if (point == RetryPoint::NormalEnemyBattle)
		{
			for (int i = 0; i < ENEMY_COUNT; i++)
			{
				EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
			}
		}

		pBoss = Instantiate<EnemyBoss>(this);

		// ���`�Ԃ���
		if (point == RetryPoint::BossLastBattle)
		{
			pBoss->ProcessStart();
			pBoss->SecondFormStart();
		}

		pPlayer = Instantiate<Player>(this);
		Instantiate<Robot>(this);

	}

	// �o�g�����y�̍Đ�
	switch (point)
	{
	case RetryPoint::NormalEnemyBattle:
		pSound->SoundPlay(SoundTrack::BattleSound);
		break;
	case RetryPoint::BossBattle:
		pSound->SoundPlay(SoundTrack::Alert);
		break;
	case RetryPoint::BossLastBattle:
		pSound->SoundPlay(SoundTrack::LastBossSound);
		break;
	default:

		break;
	}
	
}

void BattleScene::Update()
{
	// �{�X�o�ꏈ��
	if (pBoss->IsEntered() == false && EnemyManager::IsListEmpty() && isRetryProcess == false && isPauseProcess == false)
	{
		// �v���C���[�̓��͂��󂯕t���Ȃ�����
		pPlayer->SetInputReception(false);

		if (pBoss->BossEntry())
		{
			// ���y�̕ύX
			if (pSound->GetSoundFlg(SoundTrack::BossSound) == false)
			{
				pSound->SoundStop(SoundTrack::Alert);
				pSound->SoundPlay(SoundTrack::BossSound);
			}

			// �v���C���[�̓��͎�t���ĊJ����
			pPlayer->SetInputReception(true);
			pBoss->ProcessStart();

			// ���g���C�|�C���g�̍X�V
			pManager->SetRetryPoint(RetryPoint::BossBattle);
		}
		else
		{
			// Warning�̃A���[�g����炷
			if (pSound->GetSoundFlg(SoundTrack::BattleSound))
			{
				pSound->SoundStop(SoundTrack::BattleSound);
				pSound->SoundPlay(SoundTrack::Alert);
			}
		}
	}

	// �����A�s�k�摜�\�����̏���
	if (pDefeat != nullptr || pVictory != nullptr)
	{
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
		{
			// �Y�����郊�U���g�V�[���ֈڍs
			if (pVictory != nullptr)
			{
				pSound->SetSoundALLFalse();
				pManager->ChangeScene(SCENE_ID::SCENE_ID_CLEAR);
			}
			else
			{
				pSound->SetSoundALLFalse();
				pManager->SetRetryPoint(RetryPoint::NormalEnemyBattle);
				pManager->ChangeScene(SCENE_ID::SCENE_ID_OVER);
			}
		}
	}

	// �퓬�I��������
	{
		if (pPlayer->GetHP() <= 0)
		{
			const int MAX_CONTINUE = 3;	// �ő�R���e�j���[��

			// �܂��R���e�j���[�\���ǂ���
			if (pManager->GetContinueCount() < MAX_CONTINUE)
			{
				ContinueProcess();
			}
			else
			{
				pDefeat = Instantiate<DefeatImage>(this);
				PoseProcess();
			}
			
		}
		else if (pBoss->GetHP() <= 0)
		{
			pVictory = Instantiate<VictoryImage>(this);
			PoseProcess();
		}
	}
	
	// �o�g�����̃��j���[����
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) || Input::IsKeyDown(DIK_ESCAPE))
	{
		// ���j���[�摜�Ăяo��
		if (pBox == nullptr && pPause == nullptr)
		{
			pSound->SetSoundALLFalse();
			pSound->SoundPlay(SoundTrack::TitleSound);

			pPause = Instantiate<PauseImage>(this);
			pBox = Instantiate<SelectBox>(this);
			pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, BACKGAME_POS_Y, 0), true);

			PoseProcess();
			isPauseProcess = true;
		}
	}

	// �|�[�Y�摜�\�����̏���
	if (isPauseProcess)
	{
		// UI���͏���
		{
			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP) || Input::IsKeyDown(DIK_UP))
			{
				if (pSound->GetEffectFlg(SoundEffect::MoveSelection))
				{
					pSound->EffectStop(SoundEffect::MoveSelection);
				}
				pSound->EffectPlay(SoundEffect::MoveSelection);
				nowMenu = Menu::BackGame;
				pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, BACKGAME_POS_Y, 0), true);
			}

			if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || Input::IsKeyDown(DIK_DOWN))
			{
				pSound->EffectPlay(SoundEffect::MoveSelection);
				nowMenu = Menu::ToStart;
				pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, START_POS_Y, 0));
			}
		}

		// �I��
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
		{
			pSound->EffectPlay(SoundEffect::Determinant);

			isPauseProcess = false;

			switch (nowMenu)
			{
			case Menu::BackGame:
				BackBattle();
				break;
			case Menu::ToStart:
				pSound->SetSoundALLFalse();
				pManager->SetRetryPoint(RetryPoint::NormalEnemyBattle);
				pManager->ChangeScene(SCENE_ID::SCENE_ID_START);
				break;
			default:
				break;
			}
		}
	}
	else
	{
		pPlayer->SetInputReception(true);
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

void BattleScene::BattleRetry()
{
	// �R���e�j���[�񐔂����Z
	pManager->ContinueCountIncrease();

	// �{�X��AI���x�����ő�ɒB���Ă���(����U�����s����)���ǂ������m�F����
	if (pManager->GetRetryPoint() == RetryPoint::BossBattle && pBoss->GetAIState() == BossAIState::Caution)
	{
		pManager->SetRetryPoint(RetryPoint::BossLastBattle);
	}

	pManager->ReLoadScene(SCENE_ID::SCENE_ID_BATTLE);
}

void BattleScene::BackBattle()
{
	RetryPoint point = pManager->GetRetryPoint();

	pSound->SoundStop(SoundTrack::TitleSound);

	// �T�E���h�̍Đ�
	switch (point)
	{
	case RetryPoint::NormalEnemyBattle:
		pSound->SoundPlay(SoundTrack::BattleSound);
		break;
	case RetryPoint::BossBattle:
		pSound->SoundPlay(SoundTrack::BossSound);
		break;
	case RetryPoint::BossLastBattle:
		pSound->SoundPlay(SoundTrack::LastBossSound);
		break;
	default:
		break;
	}

	// �I�u�W�F�N�g�̍X�V���ĊJ
	if (EnemyManager::IsListEmpty() == false)
	{
		int nowEnemyCount = EnemyManager::GetVectorSize();

		for (int i = 0; i < nowEnemyCount; i++)
		{
			Enemy* pEnemy = EnemyManager::GetEnemyContent(i);
			pEnemy->Enter();
		}
	}

	if (point != RetryPoint::NormalEnemyBattle)
	{
		pBoss->Enter();
	}

	// �ϐ��̃��Z�b�g
	pBox->KillMe();
	pBox = nullptr;
	pPause->KillMe();
	pPause = nullptr;
}

void BattleScene::PoseProcess()
{
	if (EnemyManager::IsListEmpty() == false)
	{
		int nowEnemyCount = EnemyManager::GetVectorSize();

		for (int i = 0; i < nowEnemyCount; i++)
		{
			Enemy* pEnemy = EnemyManager::GetEnemyContent(i);
			pEnemy->Leave();
		}
	}

	pPlayer->SetInputReception(false);
	pBoss->Leave();
}

void BattleScene::ContinueProcess()
{
	// UI�̕\���ʒu�萔
	const float BOX_POS_X = -0.02f;
	const float RETORY_POS_Y = -0.06f;
	const float OVER_POS_Y = -0.425f;

	// ���g���C���邩�ǂ����̑I����������I�u�W�F�N�g���Ăяo��
	if (pBox == nullptr)
	{
		Instantiate<RetryImage>(this);
		pBox = Instantiate<SelectBox>(this);
		pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, RETORY_POS_Y, 0));

		// �|�[�Y��Ԃɂ���
		PoseProcess();
		isRetryProcess = true;
	}

	// UI���͏���
	{
		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP) || Input::IsKeyDown(DIK_UP))
		{
			pSound->EffectPlay(SoundEffect::MoveSelection);
			nowRetryMenu = RetryMenu::Retry;
			pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, RETORY_POS_Y, 0));
		}

		if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || Input::IsKeyDown(DIK_DOWN))
		{
			pSound->EffectPlay(SoundEffect::MoveSelection);
			nowRetryMenu = RetryMenu::GameOver;
			pBox->SetSelectBox(XMFLOAT3(BOX_POS_X, OVER_POS_Y, 0));
		}
	}

	// �I��
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
	{
		pSound->EffectPlay(SoundEffect::Determinant);

		isRetryProcess = false;

		switch (nowRetryMenu)
		{
		case RetryMenu::Retry:
			BattleRetry();
			break;
		case RetryMenu::GameOver:
			pSound->SetSoundALLFalse();
			pManager->SetRetryPoint(RetryPoint::NormalEnemyBattle);
			pManager->ChangeScene(SCENE_ID::SCENE_ID_OVER);
			break;
		default:
			break;
		}
	}
}
#include "sceneManager.h"


#include "../Engine/Model.h"
#include "../Engine/Image.h"
#include "../Engine/Audio.h"
#include "../Engine/Global.h"



#include "TitleScene.h"
#include "StartScene.h"
//#include "ReleaseScene.h"
//#include "OperationScene.h"
//#include "Operation2Scene.h"
//#include "PlayScene.h"
//#include "BattleScene.h"
//#include "ClearScene.h"
//#include "GameOverScene.h"
#include "DebugScene.h"


SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
	currentSceneID_ = SCENE_ID::MAX_SCENE_ID;
	nextSceneID_ = SCENE_ID::MAX_SCENE_ID;
	prevSceneID_ = SCENE_ID::MAX_SCENE_ID;

	pSound = nullptr;
}

void SceneManager::Initialize()
{
	pSound = new GameSound();

	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID::SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	prevSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);

	/*currentSceneID_ = SCENE_ID::SCENE_ID_DEBUG;
	nextSceneID_ = currentSceneID_;
	prevSceneID_ = currentSceneID_;
	Instantiate<DebugScene>(this);*/
}

void SceneManager::Update()
{
	//�V�[���؂�ւ����s�����ǂ���
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		Model::AllRelease();
		Image::AllRelease();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID::SCENE_ID_TITLE:		Instantiate<TitleScene>(this);			break;
		case SCENE_ID::SCENE_ID_START:		Instantiate<StartScene>(this);			break;
		//case SCENE_ID::SCENE_ID_RELEASE:	Instantiate<ReleaseScene>(this);		break;
		//case SCENE_ID::SCENE_ID_OPERATION:  Instantiate<OperationScene>(this);		break;
		//case SCENE_ID::SCENE_ID_OPERATION2: Instantiate<Operation2Scene>(this);		break;
		//case SCENE_ID::SCENE_ID_PLAY:       Instantiate<PlayScene>(this);			break;
		//case SCENE_ID::SCENE_ID_CLEAR:		Instantiate<ClearScene>(this);			break;
		//case SCENE_ID::SCENE_ID_OVER:		Instantiate<GameOverScene>(this);		break;
		//case SCENE_ID::SCENE_ID_BATTLE:		Instantiate<BattleScene>(this);			break;
		case SCENE_ID::SCENE_ID_DEBUG:		Instantiate<DebugScene>(this);			break;
		default:	break;
		}
		pSound->SetEffectALLFalse();
		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
	SAFE_RELEASE(pSound);
}

void SceneManager::ChangeScene(SCENE_ID next)
{
	prevSceneID_ = currentSceneID_;
	nextSceneID_ = next;
}
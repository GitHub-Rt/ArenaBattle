#include "sceneManager.h"


#include "../Engine/Model.h"
#include "../Engine/Image.h"
#include "../Engine/Audio.h"
#include "../Engine/Global.h"



#include "TitleScene.h"
#include "StartScene.h"
#include "ReleaseScene.h"
#include "KeyboardOperationScene.h"
#include "ControllerOperationScene.h"
#include "PlayScene.h"
#include "BattleScene.h"
#include "ClearScene.h"
#include "OverScene.h"
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

	//最初のシーンを準備
	/*currentSceneID_ = SCENE_ID::SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	prevSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);*/

	currentSceneID_ = SCENE_ID::SCENE_ID_DEBUG;
	nextSceneID_ = currentSceneID_;
	prevSceneID_ = currentSceneID_;
	Instantiate<DebugScene>(this);
}

void SceneManager::Update()
{
	//シーン切り替えを行うかどうか
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		KillAllChildren();

		//ロードしたデータを全削除
		Model::AllRelease();
		Image::AllRelease();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID::SCENE_ID_TITLE:		Instantiate<TitleScene>(this);			break;
		case SCENE_ID::SCENE_ID_START:		Instantiate<StartScene>(this);			break;
		case SCENE_ID::SCENE_ID_RELEASE:	Instantiate<ReleaseScene>(this);		break;
		case SCENE_ID::SCENE_ID_KEYBOARDOPERATION:  Instantiate<KeyboardOperationScene>(this);		break;
		case SCENE_ID::SCENE_ID_CONTROLLEROPERATION: Instantiate<ControllerOperationScene>(this);		break;
		case SCENE_ID::SCENE_ID_PLAY:       Instantiate<PlayScene>(this);			break;
		case SCENE_ID::SCENE_ID_CLEAR:		Instantiate<ClearScene>(this);			break;
		case SCENE_ID::SCENE_ID_OVER:		Instantiate<OverScene>(this);		break;
		case SCENE_ID::SCENE_ID_BATTLE:		Instantiate<BattleScene>(this);			break;
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
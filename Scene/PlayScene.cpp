#include "PlayScene.h"
#include "SceneManager.h"

#include "../Stage/NormalField.h"
#include "../Stage/Wall.h"
#include "../Stage/BattleStartCylinder.h"
#include "../Character/Player.h"
#include "../Character/Robot.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
	pManager = nullptr;
}

PlayScene::~PlayScene()
{

}

void PlayScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");

	Instantiate<NormalField>(this);
	Instantiate<Wall>(this);
	Instantiate<BattleStartCylinder>(this);
	Instantiate<Player>(this);
	Instantiate<Robot>(this);
}

void PlayScene::Update()
{

}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{

}

void PlayScene::BattleStart()
{
	// 二周目かどうかを調べて該当していたら画像で難易度選択を行わせる予定


	pManager->ChangeScene(SCENE_ID::SCENE_ID_BATTLE);
	//pManager->ChangeScene(SCENE_ID::SCENE_ID_DEBUG);
}
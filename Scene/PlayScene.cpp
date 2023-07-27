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
	// “ñŽü–Ú‚©‚Ç‚¤‚©‚ð’²‚×‚ÄŠY“–‚µ‚Ä‚¢‚½‚ç‰æ‘œ‚Å“ïˆÕ“x‘I‘ð‚ðs‚í‚¹‚é—\’è


	pManager->ChangeScene(SCENE_ID::SCENE_ID_BATTLE);
}
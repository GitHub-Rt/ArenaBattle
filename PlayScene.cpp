#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "Wall.h"
#include "Start.h"
#include "NormalField.h"


//デバッグ用
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	//Instantiate<Stage>(this);
	Instantiate<Wall>(this);
	Instantiate<NormalField>(this);
	Instantiate<Player>(this);
	Instantiate<Start>(this);

	//Instantiate<Enemy>(this);
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}

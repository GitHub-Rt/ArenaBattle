#include "ButtleScene.h"

#include "Player.h"
#include "Wall.h"
#include "Enemy.h"
#include "Stage.h"
#include "NormalField.h"


#include "Engine/SceneManager.h"

//コンストラクタ
ButtleScene::ButtleScene(GameObject* parent)
	: GameObject(parent, "ButtleScene")
{
}

//初期化
void ButtleScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Wall>(this);
	Instantiate<NormalField>(this);
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
}

//更新
void ButtleScene::Update()
{
}

//描画
void ButtleScene::Draw()
{
}

//開放
void ButtleScene::Release()
{
}
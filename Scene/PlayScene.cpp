#include "PlayScene.h"
#include "../Player/Player.h"
#include "../Player/HP_Gauge.h"
#include "../Enemy/Enemy.h"
#include "../Stage/Stage.h"
#include "../Stage/Wall.h"
#include "../Stage/Start.h"
#include "../Stage/NormalField.h"

#include "SceneManager.h"

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
	Instantiate<HP_Gauge>(this);

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

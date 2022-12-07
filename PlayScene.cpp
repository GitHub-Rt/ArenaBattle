#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "Wall.h"


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
	Instantiate<Stage>(this);
	Instantiate<Wall>(this);
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
	
}

//更新
void PlayScene::Update()
{
	if (eNum < 6)
	{
		time++;

		// 3秒たったら…
		if (time > 180)
		{
			//Instantiate<Enemy>(this);	//敵を出現
			time = 0;		//タイマーのリセット
			eNum++;			//敵の出現をカウント
		}
	}
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}

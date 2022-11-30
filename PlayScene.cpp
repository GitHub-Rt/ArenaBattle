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

    // 5秒ごとに　(ステージ内には最大で5体まで敵を出す)
    switch (eCount)
    {
    default:
        eCount++;

    case 300:   

        //敵が５体以下かどうか
        if (eNum < 6)
        {
            //敵を出現
            Instantiate<Enemy>(this);

            eNum++;     //敵出現したのでカウントを増やす
            eCount = 0; //敵の出現間隔をリセット

            //ステージ内に5体敵を作ったら
            if (eNum == 5)
            {
                //それ以上は敵を呼ばない　-> 敵をすべて倒したらボスを呼ぶようにする

            }
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

#pragma once
#include "Engine/GameObject.h"


//プレイシーンを管理するクラス
class PlayScene : public GameObject
{
	int eCount;	//敵を出現させる間隔
	int eNum;	//敵の出現回数

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
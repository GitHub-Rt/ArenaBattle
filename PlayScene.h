#pragma once
#include "Engine/GameObject.h"


//プレイシーンを管理するクラス
class PlayScene : public GameObject
{
	int eNum = 0;	//敵の出現数
	float time;	//敵を出現させる間隔


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
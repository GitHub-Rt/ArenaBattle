#pragma once
#include "Engine/GameObject.h"


//■■シーンを管理するクラス
class ButtleScene : public GameObject
{
	int eNum;	//敵の出現数
	int eCount;	//敵の出現間隔
	
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ButtleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
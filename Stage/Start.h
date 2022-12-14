#pragma once
#include "../Engine/GameObject.h"

//バトルスタートモデルを管理するクラス
class Start : public GameObject
{
    int hModel_;    //モデル番号
    
public:
    //コンストラクタ
    Start(GameObject* parent);

    //デストラクタ
    ~Start();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;
};
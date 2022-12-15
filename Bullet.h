#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Bullet : public GameObject
{
    int hModel_;    //モデル番号
    XMFLOAT3 move;  //移動
    int disNum;    //方向の番号

public:
    //コンストラクタ
    Bullet(GameObject* parent);

    //デストラクタ
    ~Bullet();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetMoveNum(XMFLOAT3 move_, int num) { move = move_; disNum = num; }

    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;
};
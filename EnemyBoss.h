#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class EnemyBoss : public GameObject
{
    const FLOAT HALF_HEIGHT = 17.0f;

    int hModel_;    //モデル番号
    
public:
    //コンストラクタ
    EnemyBoss(GameObject* parent);

    //デストラクタ
    ~EnemyBoss();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};
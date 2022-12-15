#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class EnemyBoss : public GameObject
{

    int hModel_;    //モデル番号
    
    int countB;      //弾攻撃を管理するカウント
    int bulletC;    //弾攻撃の１発ごとの間隔
    int bulletNum;  //１回の弾攻撃で出す総個数 (上限数は8)
    bool isBulletEnd;   //弾攻撃が終わったかどうか
    
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
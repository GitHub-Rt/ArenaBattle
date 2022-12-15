#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class EnemyBoss : public GameObject
{

    int hModel_;    //モデル番号
    
    //弾攻撃に関する変数
    int countB;      //弾攻撃全体を管理するカウント
    int bulletRotateC;  //攻撃後に回転するときのカウント
    int bulletC;    //弾攻撃の１発ごとの間隔
    int bulletNum = 1;  //１回の弾攻撃で出す総個数 (上限数は8)
    bool isBulletStart;   //弾攻撃が開始したかどうか
    bool isRotate;      //回転したかどうか
    
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

    bool GetRotate() { return isRotate; }
};
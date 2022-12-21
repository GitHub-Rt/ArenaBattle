#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class EnemyBoss : public GameObject
{
    int hModel_[2];    //モデル番号(1 : ノーマル時,2 : 被ダメージ時)
    float HP = 30.0f;   //HP
    float prevHP = HP;  //以前のHP
    bool isDamage;      //いまダメージを受けているかどうか
    
    
    //攻撃

    bool isAttack;  //今攻撃中かどうか
    int attackNum;  //攻撃番号を格納

    //弾攻撃に関する変数(攻撃番号 : 1番)
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

    //何かに当たった
    void OnCollision(GameObject* pTarget) override;

    //回転しているかどうか
    bool GetRotate() { return isRotate; }
};
#pragma once
#include "../../Engine/GameObject.h"

//敵ボスを管理するクラス
class EnemyBoss : public GameObject
{
    //定数定義
    const FLOAT MAX_HP = 50.0f; //最大HP
    const FLOAT CIRCLE_RANGE = 3600.0f;         //床の移動可能範囲円の半径の2乗

    int hModel_[2];    //モデル番号(1 : ノーマル時,2 : 被ダメージ時)
    float HP = MAX_HP;   //HP
    float prevHP = HP;  //以前のHP
    bool isDamage;      //いまダメージを受けているかどうか
    
    
    //攻撃
    enum State
    {
        NoAttack = 0,   //未攻撃
        BulletAttack,   //弾攻撃  1
        RotationAttack, //渦巻移動攻撃  2
        WavesAttack,    //波状攻撃 (特殊攻撃後から)  3
        JumpAttack,     //ジャンプ攻撃 (特殊攻撃後から)  4
        SpecialAttack   //特殊攻撃(残り体力が30%切ったら発動) 全体爆発(プレイヤーの体力全体の3割ダメージを与える)
        
    };
    State attackNum;  //攻撃番号を格納

    bool isAttack;  //今攻撃中かどうか
    

    //弾攻撃に関する変数
    int countB;      //弾攻撃全体を管理するカウント
    int bulletRotateC;  //攻撃後に回転するときのカウント
    int bulletC;    //弾攻撃の１発ごとの間隔
    int bulletNum = 1;  //１回の弾攻撃で出す総個数 (上限数は8)
    bool isBulletStart;   //弾攻撃が開始したかどうか
    bool isRotate;      //回転したかどうか


    //渦巻攻撃に関する変数
    bool isRotationStart;   //回転攻撃を開始したかどうか
    bool isEndLine;         //移動可能範囲の端まで行ったかどうか
    float radius = 1.5f;   //半径の初期値
    float angle = 0.05f;    //変化の角度
    XMFLOAT3 firstPos = { 0,0,0 };  //最初のポジション

    //波状攻撃に関する変数
    bool isWavesStart;      //波状攻撃を開始したかどうか
    

    //ジャンプ攻撃に関する変数
    bool isJumpStart;       //ジャンプ攻撃を開始したかどうか


    //特殊攻撃に関する変数
    bool isSpacial;     //特殊攻撃を使ったかどうか

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




#if _DEBUG

    int GetAttackPattern() { return attackNum; }

#endif
};
#pragma once
#include "Engine/GameObject.h"




//敵を管理するクラス
class Enemy : public GameObject
{
    //定数宣言
    const FLOAT HALF_HEIGHT = 1.5f;     //オブジェクトの半分の高さ
    const FLOAT MAX_HP = 1.0f;          //最大HP
    const FLOAT EP_LENGTH = 2.5f;       //敵とプレイヤー間の距離

    int hModel_;    //モデル番号
    int pAcom;      //アタックの種類を保存
    
    
    float HP = MAX_HP;  //敵HP
    float amountMove = 0.125f; //移動量

    XMFLOAT3 pCurrentPos;   //プレイヤーの現在位置
    XMFLOAT3 eCurrentPos;   //自分自身(敵)の現在位置
    XMFLOAT3 nextPos;       //自分自身(敵)の次の位置

    XMVECTOR prevPos;       //自分自身(敵)が以前いた場所

    //フラグ判定
    bool eAttackS_; //攻撃判定管理
    bool pAttackS_; //プレイヤーの攻撃状態
    bool pAlive;    //プレイヤーが生きているかどうか
    bool someFlag;
    

public:
    //コンストラクタ
    Enemy(GameObject* parent);

    //デストラクタ
    ~Enemy();

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

    XMFLOAT3 GetPosition();

    //敵の状態
    bool EGetCondition();
    void ESetFalse(bool attackFlg_);
    bool EGetAlive();
    
};
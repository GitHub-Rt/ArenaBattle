#pragma once
#include "../Engine/GameObject.h"



//プレイヤーを管理するクラス
class Player : public GameObject
{

    //定数
    const FLOAT JUMPSPEED = 20.0f;              //ジャンプ時の初速度
    const FLOAT GRAVITY = 0.5f;                 //重力
    const FLOAT HALF_HEIGHT = 1.25f;            //オブジェクトの半分の高さ
    const FLOAT PC_LENGTH = -30.0f;             //カメラからプレイヤーまでの距離
    const FLOAT CAMERA_ANGLE_SPEED = 0.025f;    //カメラの旋回スピード
    const FLOAT MAX_CAMERA_UP = 1.0f;           //カメラの上方向の最大値
    const FLOAT MAX_CAMERA_DOWN = 0.0f;         //カメラの下方向の最大値
    const FLOAT MAX_HP = 50.0f;                 //最大HP
    const FLOAT NOUGHT = 0;                     //０の時を表す
    const FLOAT CIRCLE_RANGE = 3600.0f;         //床の移動可能範囲円の半径の2乗
    const FLOAT PB_LENGTH = 13.0f;              //敵ボスとプレイヤーの距離

    //ローカル変数
    int hModel_[2];       //モデル番号 ( 0 : Normal, 1 : Damege)
    int count_;        //ジャンプカウント
    int attackNum;    //攻撃の種類
    int aCount;       //強攻撃時のカウント管理
    int eCount;       //回避時のカウント
    float checkYG;     //ジャンプ時の座標保存
    float initVec = JUMPSPEED;  //ジャンプ(戦闘時)
    float initVecNor = JUMPSPEED;           //ジャンプ(非戦闘時)
    float moveLimit;    //円周にいるかどうか
    float dis;          //原点からの距離
    // ※カメラには初期角度を入れておく
    float angleX = 0.0f;        //カメラの水平方向(横回転) 
    float angleY = 0.25f;       //カメラの鉛直方向(縦回転)
    
    XMFLOAT3 move;  //プレイヤーの移動入力の値を格納


    float HP = MAX_HP; //体力
    float prevHP = HP;  //前回の体力


    XMVECTOR vPrevPos;       //前回いたポジションを保存(XMVECTOR)
    XMFLOAT3 prevPos;        //前回いたポジションを保存(XMFLOAT3)

    //カメラ関連
    XMVECTOR playerAngle;   //プレイヤーの角度を保存
    XMMATRIX mRotateX;   //カメラの回転行列(水平方向)
    XMMATRIX mRotateY;   //カメラの回転行列(鉛直方向)

    //フラグ関係
    bool pAttackS_;      //攻撃判定管理
    bool attackFlg;     //プレイヤー自身の攻撃全体の管理
    bool eAttackS_;     //敵の攻撃状態
    bool jumpFlg;       //ジャンプフラグ管理
    bool jumpTopFlg;    //ジャンプの頂上管理 
    bool moveFlg = true;       //プレイヤーの移動管理
    bool aliveFlg;      //生きてるかどうか
    bool eAlive;        //敵が生きているかどうか
    bool isBoss = true;        //ボスキャラの行動によって飛ばされる判定管理
    bool isDamage;      //ダメージを受けているかどうか


    
public:
    Player(GameObject* parent);
    ~Player();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void OnCollision(GameObject* pTarget) override;


    //プレイヤーの状態関連

    /// <summary>
    /// プレイヤーの攻撃フラグをFALSEにする
    /// </summary>
    /// <param name="attackFlg_">プレイヤー全体の攻撃判定</param>
    void PSetFalse(bool attackFlg_);

    /// <summary>
    /// プレイヤーが攻撃を行っているかどうかを取得
    /// </summary>
    /// <returns>true → 攻撃中, false → 未攻撃</returns>
    bool PGetCondition();

    /// <summary>
    /// プレイヤーの攻撃番号を格納
    /// </summary>
    /// <param name="attackNum_">攻撃種類番号</param>
    void PSetAttack(int attackNum_);
    
    /// <summary>
    /// プレイヤーの攻撃番号を獲得
    /// </summary>
    /// <returns>攻撃種類番号</returns>
    int PGetAttack();
    
    /// <summary>
    /// プレイヤーが生きているかどうかを取得
    /// </summary>
    /// <returns>true → 生きている, false → 生きていない</returns>
    bool PGetAlive();

    /// <summary>
    /// プレイヤーの現在位置を取得
    /// </summary>
    /// <returns>XMFLOAT3</returns>
    XMFLOAT3 GetPosition();



#ifdef _DEBUG

    bool isInv; //無敵状態かどうか
    bool isDying;   //瀕死状態かどうか
    void SetInvincible()
    {
        isInv = true;
    }
    void SetDying()
    {
        isDying = true;
    }

#endif



};
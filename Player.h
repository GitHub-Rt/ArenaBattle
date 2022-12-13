#pragma once
#include "Engine/GameObject.h"



//プレイヤーを管理するクラス
class Player : public GameObject
{

    //定数
    const FLOAT JUMPSPEED = 20.0f;           //ジャンプ時の初速度
    const FLOAT GRAVITY = 0.5f;            //重力
    const FLOAT HALF_HEIGHT = 1.25f;         //オブジェクトの半分の高さ
    const FLOAT PC_LENGTH = -30.0f;         //カメラからプレイヤーまでの距離
    const FLOAT CAMERA_ANGLE_SPEED = 0.025f; //カメラの旋回スピード
    const FLOAT MAX_CAMERA_UP = 1.0f;      //カメラの上方向の最大値
    const FLOAT MAX_CAMERA_DOWN = 0.0f;     //カメラの下方向の最大値
    const FLOAT MAX_HP = 50.0f;          //最大HP
    const FLOAT NOUGHT = 0;             //０の時を表す
    const FLOAT CIRCLE_RANGE = 3600.0f;   //床の移動可能範囲円の半径

    //ローカル変数
    int hModel_;       //モデル番号
    int count_;        //ジャンプカウント
    int attackNum;    //攻撃の種類
    int aCount;       //強攻撃時のカウント管理
    int eCount;       //回避時のカウント
    float checkYG;     //ジャンプ時の座標保存
    float initVec = JUMPSPEED;  //ジャンプ(戦闘時)
    float initVecNor = JUMPSPEED;           //ジャンプ(非戦闘時)
    float moveLimit;    //円周にいるかどうか
    // ※カメラには初期角度を入れておく
    float angleX = 0.0f;        //カメラの水平方向(横回転) 
    float angleY = 0.25f;       //カメラの鉛直方向(縦回転)
    
    XMFLOAT3 move;


    float HP = MAX_HP; //体力


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


    
public:
   //引数ありコンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;


    //プレイヤーの状態
    void PSetFalse(bool attackFlg_);
    bool PGetCondition();
    void PSetAttack(int attackNum_);
    int PGetAttack();
    bool PGetAlive();

    //現在位置
    void SetPosition(XMFLOAT3 position_);
    XMFLOAT3 GetPosition();

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //何かに当たった
    void OnCollision(GameObject* pTarget) override;
   
};
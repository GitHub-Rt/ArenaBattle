#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "Wall.h"

//デバッグ用
#include "Engine/Input.h"
#include "Engine/SceneManager.h"



//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1),count_(0), aliveFlg(true)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("player.fbx");
    assert(hModel_ >= 0);

    //当たり判定枠
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.2f);
    AddCollider(collision);

}

//更新
void Player::Update()
{

    //ステージ情報獲得
    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

    //レイをステージに飛ばす
    RayCastData data;
    data.start = transform_.position_;            //レイの発射位置
    data.dir = XMFLOAT3(0.0f, -1.0f, 0.0f);       //レイの方向
    Model::RayCast(hGroundModel, &data);           //レイを発射

    //レイが当たったら
    if (data.hit)
    {
        //位置を下げる
        transform_.position_.y -= data.dist - HALF_HEIGHT;

    }


    //////////////////////   移動処理    //////////////////////////

    //float moveX, moveZ;

    //////////////  キーボード  /////////

    //if (angle != 0.0f)
    //{
    //    //カメラの角度が変化した
    //    moveX = 1 * angle;
    //    moveZ = 1 * angle;
    //}
    //else
    //{
    //    //カメラの角度変化なし
    //    moveX = 1;
    //    moveZ = 1;
    //}
    //
    //XMVECTOR vKeyX = XMVectorSet(moveX, 0, 0, 0);    //横方向のベクトル
    //XMVECTOR vKeyZ = XMVectorSet(0, 0, moveZ, 0);    //縦(奥)方向のベクトル

    ////斜め方向のベクトル(正規化)
    //XMVECTOR vKeyOblipue_X = XMVector3Normalize(vKeyX);
    //XMVECTOR vKeyOblipue_Z = XMVector3Normalize(vKeyZ);
    //
    ////型変換
    //XMFLOAT3 moveKeyX, moveKeyZ;
    //XMStoreFloat3(&moveKeyX, vKeyOblipue_X);
    //XMStoreFloat3(&moveKeyZ, vKeyOblipue_Z);
    //
    //if (Input::IsKey(DIK_W))
    //{
    //    //前進
    //    transform_.position_.z += moveKeyZ.z * 0.125f;
    //}
    //if (Input::IsKey(DIK_D))
    //{
    //    //右方向
    //    transform_.position_.x += moveKeyX.x * 0.215f;
    //}
    //if (Input::IsKey(DIK_S))
    //{
    //    //後退
    //    transform_.position_.z -= moveKeyZ.z * 0.125f;
    //}

    //if (Input::IsKey(DIK_A))
    //{
    //    //左方向
    //    transform_.position_.x -= moveKeyX.x * 0.125f;
    //}

    //if (Input::IsKeyDown(DIK_SPACE) && jumpFlg == false)
    //{
    //    //ジャンプ
    //    jumpFlg = true; //trueの間はジャンプできない(二段ジャンプ未実装 -> ※検討中)
    //    //ジャンプ前の座標の保存
    //    checkYG = (transform_.position_.y + HALF_HEIGHT);
    //}

    //////////  コントローラー  /////////

    //プレイヤーの移動量
    
    move = Input::GetPadStickL(0);

    
    if (move.x != NOUGHT ||  move.y != NOUGHT)
    {
        moveFlg = true;
    }

    //プレイヤーのベクトル
    XMVECTOR vCom = XMVectorSet(move.x, 0, move.y, 0);
    prevPos = XMLoadFloat3(&transform_.position_);

    //////////////////  モデルの回転  /////////////////////


    //カメラの位置から焦点に向かうベクトル
    XMFLOAT3 CPos, CTar;
    CPos = Camera::GetPosition();
    CTar = Camera::GetTarget();
    XMVECTOR vCPos = XMLoadFloat3(&CPos);
    XMVECTOR vCTar = XMLoadFloat3(&CTar);
    XMVECTOR vFront = vCTar - vCPos;

    //ｙを０にする
    XMFLOAT3 fC;
    XMStoreFloat3(&fC, vFront);
    fC.y = 0;
    vFront = XMLoadFloat3(&fC);
    vFront = XMVector3Normalize(vFront);

    //カメラの角度が変化したか
    if (angle != 0.0f)
    {
        //カメラの角度に合わせてプレイヤーベクトルを回転
        XMMATRIX mCamRotate = XMMatrixRotationY(angle);
        vCom = XMVector3TransformCoord(vCom, mCamRotate);
    }
        
    //斜め方向のベクトル(正規化)
    XMVECTOR vComOblipue_ = XMVector3Normalize(vCom);

    if (moveFlg == true) 
    {
        //frontとmoveの内積を求める
        XMVECTOR vecDot = XMVector3Dot(vFront, vComOblipue_);


        //向いている角度を求める（ラジアン）
        float dot = XMVectorGetX(vecDot);
        float angleR = acos(dot);

        //もとから向いているベクトルと動くベクトルの外積
        XMVECTOR cross = XMVector3Cross(vFront, vComOblipue_);

        //外積の結果のYがマイナス　＝　下向き　＝ 左に進んでいる　
        if (XMVectorGetY(cross) < 0)
        {
            angleR *= -1;
        }

        //角度の保存
        float rotateY  = angleR * 180.0f / 3.14f;
        
        //ベクトルにセットしてカメラの回転行列をかける
        playerAngle = XMVectorSet( 0, rotateY, 0, 0 );
        playerAngle = XMVector3TransformCoord(playerAngle, mRotate);

        //フラグのリセット
        moveFlg = false;
    }
    //回転
    transform_.rotate_.y = XMVectorGetY(playerAngle);

    
    //型変換
    XMFLOAT3 moveCom;
    XMStoreFloat3(&moveCom, vComOblipue_);
    
    //移動量の調整
    moveCom.x = moveCom.x * 0.25f;
    moveCom.z = moveCom.z * 0.25f;

    //移動
    transform_.position_.x += moveCom.x;
    transform_.position_.z += moveCom.z;

    //Aボタンを押したら
    if (Input::IsPadButtonDown(0, XINPUT_GAMEPAD_A))
    {
        //ジャンプ
        jumpFlg = true; //trueの間はジャンプできない(二段ジャンプ未実装 -> ※検討中)

        //ジャンプ前の座標の保存
        checkYG = (transform_.position_.y + HALF_HEIGHT);
    }


    //////////////////////////  ジャンプ処理  ///////////////////////////////
    if (jumpFlg == true)
    {
        transform_.position_.y += initVec;     //速度でY座標を変化 ←　今後変更ジャンプの挙動をもっと自然に
        initVec = initVec - GRAVITY;

        if (transform_.position_.y > checkYG)
        {
            //重力を加え続ける
            transform_.position_.y += initVec;
            initVec = initVec - GRAVITY;
            if (initVec <= 0 && jumpTopFlg == false)
            {
                //ジャンプの頂上で少し停止
                jumpTopFlg = true;
                Sleep(3);
            }
        }
        if (transform_.position_.y < checkYG)
        {
            //再度ジャンプを可能にする(変数の初期化)
            jumpFlg = false;
            transform_.position_.y = checkYG;
            initVec = JUMPSPEED;
            return;
        }
    }
    
    //////////////////////  攻撃処理     //////////////////////

    //マウスの左クリックが押された、PadのBボタンが押された
    if ( Input::IsMouseButtonDown(0) ||  Input::IsPadButtonDown(0, XINPUT_GAMEPAD_B))
    {

        //通常攻撃
        attackNum = 1;
        //モーション

        //当たったか判定
        if (pAttackS_ == false)
        {
            pAttackS_ = true;
        }
    }
    //Qが押された、PadのYが押された
    if ( Input::IsKeyDown(DIK_Q) ||  Input::IsPadButtonDown(0, XINPUT_GAMEPAD_Y))
    {
        //強攻撃
        attackNum = 2;
        //モーション

        //当たったか判定(ちょっと当たり範囲広めがいいかも...)
        if (pAttackS_ == false)
        {
            pAttackS_ = true;
        }
    }

    //////////////////////////　カメラ  /////////////////////////

    //プレイヤーの現在位置を取得
    XMFLOAT3 nowPos = GetPosition();
    XMVECTOR vPos = XMLoadFloat3(&nowPos);
    
    //右スティックでカメラをプレイヤー中心に回転させる
    if (Input::GetPadStickR(0).x < 0.0f )
    {
        //右スティックを左に倒したら
        angle -= CAMERA_ANGLE_SPEED;
    }
    
    else if (Input::GetPadStickR(0).x > 0.0f )
    {
        //右スティックを右に倒したら
        angle += CAMERA_ANGLE_SPEED;
    }

    //回転行列
    mRotate = XMMatrixRotationY(angle);

    //プレイヤーからカメラへのベクトル
    XMVECTOR vCam = XMVectorSet(0.0f, 3.0f, PC_LENGTH, 0.0f);

    //カメラの角度
    XMVECTOR vRotate = XMVector3TransformCoord(vCam, mRotate);
    
    //プレイヤーの動きにカメラを追従させるために移動行列作成
    XMMATRIX mMove = XMMatrixTranslation(moveCom.x, moveCom.y,moveCom.z);
    
    //カメラの位置
    XMVECTOR vCamPos = XMVector3TransformCoord(vRotate, mMove) + vPos;

    //逆ベクトルの正規化
    XMVECTOR vFocusUnit = -vCam;
    XMVECTOR vFocus = XMVector3Normalize(vFocusUnit);
    vFocus *= 4.5f;
    
    //焦点の位置
    XMVECTOR vCamFoc = vFocus + vPos;
    
    //型変換
    XMFLOAT3 camPos, camFoc;
    XMStoreFloat3(&camPos, vCamPos);
    XMStoreFloat3(&camFoc, vCamFoc);

    //カメラの設定
    Camera::SetPosition(camPos);
    Camera::SetTarget(camFoc);


    ///////////////////////   敵の攻撃    ///////////////////////////////

    //敵の状態確認
    Enemy* eStatus = (Enemy*)FindObject("Enemy");
    //存在するかどうかを確認
    if (eStatus == NULL)
    {
        //敵はもう存在しない
        MessageBox(NULL, "敵を倒しました。OKボタンを押した後にスタートボタンを押してください", "Game Clear", MB_OK);
        
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_CLEAR);
    }
    else
    {
        eAttackS_ = eStatus->EGetCondition();
        if (eAttackS_ == true)
        {
            HP -= 0.25f;
            eStatus->ESetFalse(eAttackS_);
        }
        SAFE_RELEASE(eStatus);

    }
   
    //HPがなくなったら
    if (HP <= 0)
    {
        HP = MAX_HP;
        aliveFlg = false;
        KillMe();
    }

}


//プレイヤーの状態
void Player::PSetFalse(bool attackFlg_)
{
    attackFlg_ = false;
    pAttackS_ = false;
}

bool Player::PGetCondition()
{
    return pAttackS_;
}

void Player::PSetAttack(int attackNum_)
{
    attackNum_ = attackNum;
}


int Player::PGetAttack()
{
    return attackNum;
}


//現在位置
void Player::SetPosition(XMFLOAT3 position_)
{
    position_ = transform_.position_;
}

XMFLOAT3 Player::GetPosition()
{
    return transform_.position_;
}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}

//オブジェクトに当たった
void Player::OnCollision(GameObject* pTarget)
{
    //敵に攻撃時以外で当たったときの処理
    if (pTarget->FindObject("Enemy") )
    {
        if (pAttackS_ == false)
        {
            //これ以上その先へは進めなくする
            XMStoreFloat3(&transform_.position_, prevPos);
        }
    }
}

bool Player::PGetAlive() 
{
    return aliveFlg; 
}

////壁かどうかの判別
//bool Player::IsWall()
//{
//    
//}




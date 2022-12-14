#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "NormalField.h"
#include "Wall.h"
#include "Start.h"
#include "EnemyBoss.h"


#include <cmath>


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
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.5f);
    AddCollider(collision);

    transform_.position_.z = -45.0f;

}

//更新
void Player::Update()
{
    //ボスキャラが出たら円の端まで吹き飛ぶ
    EnemyBoss* pBoss = (EnemyBoss*)FindObject("EnemyBoss");
    if (pBoss != nullptr)
    {

        if (isBoss == true)
        {

            moveFlg = false;

            //原点から今のプレイヤーまでのベクトルを用意

            float posX = transform_.position_.x;
            float posZ = transform_.position_.z;

            XMVECTOR vNowPosXZ = XMVectorSet(posX, 0, posZ, 0);

            XMFLOAT3 origin = XMFLOAT3(0, 0, 0);
            XMVECTOR vNormal = XMLoadFloat3(&origin);

            XMVECTOR vNowPos = vNowPosXZ - vNormal;

            //ベクトルの長さを求める

            vNowPos = XMVector3Length(vNowPos);
            dis = XMVectorGetX(vNowPos);

            //ベクトルの長さが、バトルフィールドの端までの長さと同じになるまでベクトル方向にプレイヤーを移動させる

            if (powf(dis, 2.0f) < CIRCLE_RANGE)
            {
                vNowPos = XMVector3Normalize(vNowPos);
                XMFLOAT3 nextPos;
                XMStoreFloat3(&nextPos, vNowPos);

                //移動
                if (transform_.position_.x < 0)
                {
                    transform_.position_.x -= nextPos.x * 4.5f;
                }
                else
                {
                    transform_.position_.x += nextPos.x * 4.5f;
                }
                if (transform_.position_.z < 0)
                {
                    transform_.position_.z -= nextPos.z * 4.5f;
                }
                else
                {
                    transform_.position_.z += nextPos.z * 4.5f;
                }
            }
            
        }
    }


    Start* pStart = (Start*)FindObject("Start");
    if (pStart == NULL)
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




        //移動可能範囲かどうかの判定(移動可能範囲はStageの部分のみ。Model➡ButtleField.fbx)
        moveLimit = powf(transform_.position_.x, 2.0f) + powf(transform_.position_.z, 2.0f);

        if (moveLimit > CIRCLE_RANGE)
        {
            //これ以上その先へは進めなくする
            XMStoreFloat3(&transform_.position_, vPrevPos);

            if (isBoss == true)
            {
                isBoss = false;
                moveFlg = true;
            }
        }



        //////////////////////////  ジャンプ処理  ///////////////////////////////

        //Aボタンを押したら
        if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A, 0))
        {
            //ジャンプ
            jumpFlg = true; //trueの間はジャンプできない(二段ジャンプ未実装 -> ※検討中)

            //ジャンプ前の座標の保存
            checkYG = (transform_.position_.y + HALF_HEIGHT);
        }


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



        ///////////////////////   敵の攻撃    ///////////////////////////////

        //敵の状態確認
        Enemy* eStatus = (Enemy*)FindObject("Enemy");
        //存在するかどうかを確認
        if (eStatus != NULL)
        {
            eAttackS_ = eStatus->EGetCondition();
            if (eAttackS_ == true)
            {
                HP -= 0.25f;


                //被ダメージモーション


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
    else
    {

        //ステージ情報獲得
        NormalField* pNormalField = (NormalField*)FindObject("NormalField");    //ステージオブジェクトを探す
        int hGroundModel = pNormalField->GetModelHandle();    //モデル番号を取得

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


        //////////////////////////  ジャンプ処理  ///////////////////////////////

            //Aボタンを押したら
        if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A, 0) && jumpFlg == false)
        {
            //ジャンプ
            jumpFlg = true; //trueの間はジャンプできない(二段ジャンプ未実装 -> ※検討中)

            //ジャンプ前の座標の保存
            checkYG = (transform_.position_.y + HALF_HEIGHT);
        }


        if (jumpFlg == true)
        {
            transform_.position_.y += initVecNor;     //速度でY座標を変化 ←　今後変更ジャンプの挙動をもっと自然に
            initVecNor = initVecNor - GRAVITY;

            if (transform_.position_.y > checkYG)
            {
                //重力を加え続ける
                transform_.position_.y += initVecNor;
                initVecNor = initVecNor - GRAVITY;
                if (initVecNor <= 0 && jumpTopFlg == false)
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
                initVecNor = JUMPSPEED;
                return;
            }
        }


    }




    //////////////////////   移動処理  (コントローラーのみ対応)    //////////////////////////

        //プレイヤーの移動
    move = Input::GetPadStickL(0);

    //プレイヤーのベクトル
    XMVECTOR vCom = XMVectorSet(move.x, 0, move.y, 0);
    vPrevPos = XMLoadFloat3(&transform_.position_);

    //////////////////    モデルの回転  ・　移動　　  /////////////////////


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
    if (angleX != 0.0f)
    {
        //カメラの角度に合わせてプレイヤーベクトルを回転
        XMMATRIX mCamRotate = XMMatrixRotationY(angleX);
        vCom = XMVector3TransformCoord(vCom, mCamRotate);
    }

    //斜め方向のベクトル(正規化)
    XMVECTOR vComOblipue_ = XMVector3Normalize(vCom);

    //型変換
    XMFLOAT3 moveCom;
    XMStoreFloat3(&moveCom, vComOblipue_);

    //移動量の調整
    moveCom.x = moveCom.x * 0.25f;
    moveCom.z = moveCom.z * 0.25f;

    //攻撃中は移動できない  ※回避はいつでもできる
    if (moveFlg == true)
    {
        //移動
        transform_.position_.x += moveCom.x;
        transform_.position_.z += moveCom.z;

        //モデル自身の回転
        if (moveCom.x != 0 || moveCom.z != 0)
        {
            transform_.rotate_.y = atan2(moveCom.x, moveCom.z) * 180.0 / 3.14;
        }



    }

    //回避 (R2ボタンで回避) ➡　攻撃中断もできる

    if (Input::GetPadTrrigerR(0) != NULL)
    {

        if (eCount < 20)
        {
            //回避
            transform_.position_.x += moveCom.x * 2.5f;
            transform_.position_.z += moveCom.z * 2.5f;
            eCount++;
        }
        else
        {
            eCount = 0;
        }

        attackFlg = false;
        moveFlg = true;
    }


    
    //////////////////////  攻撃処理     //////////////////////

        //いま攻撃を行えるかどうか
    if (attackFlg == false)
    {
        //PadのBボタンが押された
        if (Input::IsPadButtonDown(XINPUT_GAMEPAD_B, 0))
        {
            //通常攻撃
            attackNum = 1;


            //攻撃しているかどうか判定
            if (pAttackS_ == false)
            {
                pAttackS_ = true;
            }
            attackFlg = true;
            moveFlg = false;
        }

        //PadのYが押された
        if (Input::IsPadButtonDown(XINPUT_GAMEPAD_Y, 0))
        {
            //強攻撃
            attackNum = 2;


            //攻撃しているかどうか判定
            if (pAttackS_ == false)
            {
                pAttackS_ = true;
            }
            attackFlg = true;
            moveFlg = false;
        }
    }




    //モーション
    if (attackNum != NULL)
    {
        switch (attackNum)
        {
        case 1:
            //通常攻撃
            //体当たりにようなモーション

            if (aCount < 30)
            {
                //少し後ろに下がる
            }
            else if (aCount == 30)
            {
                //攻撃したときの位置に戻る
            }
            else
            {
                aCount = 0;
                attackNum = NULL;
                moveFlg = true;
                attackFlg = false;
            }


            aCount++;


            break;

        case 2:

            //強攻撃
            //回転して薙ぎ払うようなモーション
            if (aCount <= 90)
            {
                transform_.rotate_.y += 12.0f;
            }
            else
            {
                aCount = 0;
                attackNum = NULL;
                moveFlg = true;
                attackFlg = false;
            }

            aCount++;

            break;
        }

    }


    //////////////////////////　カメラ  /////////////////////////

       //プレイヤーの現在位置を取得
    XMFLOAT3 nowPos = GetPosition();
    XMVECTOR vPos = XMLoadFloat3(&nowPos);

    //右スティック横方向でカメラをプレイヤー中心に回転させる
    if (Input::GetPadStickR(0).x != NULL)
    {
        if (Input::GetPadStickR(0).x < 0.0f)
        {
            //右スティックを左に倒したら
            angleX -= CAMERA_ANGLE_SPEED;
        }

        else if (Input::GetPadStickR(0).x > 0.0f)
        {
            //右スティックを右に倒したら
            angleX += CAMERA_ANGLE_SPEED;
        }


    }


    //右スティック縦方向でカメラをプレイヤー中心に円回転させる
    if (Input::GetPadStickR(0).y != NULL)
    {

        //右スティックを下に倒した
        if (Input::GetPadStickR(0).y < 0.0f)
        {
            angleY += CAMERA_ANGLE_SPEED;

            //上方向の最大値に到達しているかどうか
            if (angleY > MAX_CAMERA_UP)
            {
                angleY = MAX_CAMERA_UP;
            }
        }

        //右スティックを上に倒した
        else if (Input::GetPadStickR(0).y > 0.0f)
        {
            angleY -= CAMERA_ANGLE_SPEED;

            //下方向の最大値に到達しているかどうか
            if (angleY < MAX_CAMERA_DOWN)
            {
                angleY = MAX_CAMERA_DOWN;
            }
        }

    }

    //カメラ角度のリセット(スタートボタンでリセット)
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START, 0))
    {
        angleX = 0.0f;
        angleY = 0.25f;
    }

    //行列を変化
    mRotateX = XMMatrixRotationY(angleX);
    mRotateY = XMMatrixRotationX(angleY);

    //プレイヤーからカメラへのベクトル
    XMVECTOR vCam = XMVectorSet(0.0f, 3.0f, PC_LENGTH, 0.0f);

    //カメラの角度
    XMVECTOR vRotate = XMVector3TransformCoord(vCam, mRotateY);     //縦方向の行列で変形
    vRotate = XMVector3TransformCoord(vRotate, mRotateX);              //横方向の行列で変形

    //プレイヤーの動きにカメラを追従させるために移動行列作成
    XMMATRIX mMove = XMMatrixTranslation(moveCom.x, moveCom.y, moveCom.z);

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
            XMStoreFloat3(&transform_.position_, vPrevPos);
        }
    }
}

bool Player::PGetAlive() 
{
    return aliveFlg; 
}


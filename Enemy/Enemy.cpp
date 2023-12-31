﻿#include "Enemy.h"
#include "../Stage/Stage.h"
#include "../Player/Player.h"
#include "../Engine/Model.h"
#include "../Engine/BoxCollider.h"
#include "../Engine/Global.h"
#include "../Scene/SceneManager.h"
#include "../Scene/PlayScene.h"


//コンストラクタ
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1)
{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("enemy.fbx");
    assert(hModel_ >= 0);

    transform_.position_.x = (float)(rand() % 100 - 50);
    transform_.position_.z = 15.0f;

    //当たり判定枠
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(4, 5, 3));
    AddCollider(collision);
}

//更新
void Enemy::Update()
{


    
    //ダメージモーション中かどうか
    if (isDamege == false)
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
            transform_.position_.y -= (data.dist - HALF_HEIGHT);

        }



        ///////////////////////////　移動  /////////////////////////////


        //プレイヤー、敵の座標を取得
        Player* pPlayer = (Player*)FindObject("Player");

        //生きてるかどうかを確認
        if (pPlayer == nullptr)
        {
            //Updateを途中でやめる
            Leave();
        }
        else
        {
            //生きている
            pAlive = pPlayer->PGetAlive();
            if (pAlive == true)
            {
                //攻撃状況を把握(攻撃していなかったら...)
                pAcom = pPlayer->PGetAttack();
                if (pAcom == NULL)
                {
                    //攻撃番号を初期化
                    pPlayer->PSetFalse(pAttackS_);
                }
                //プレイヤーの位置取得
                pCurrentPos = pPlayer->GetPosition();
            }
        }
        //敵自身の位置取得
        eCurrentPos = GetPosition();

        prevPos = XMLoadFloat3(&eCurrentPos);

        //プレイヤー座標から敵座標を引く
        vMove = XMLoadFloat3(&pCurrentPos) - prevPos;
        prevVec = vMove;


        //ベクトルの長さを求める
        XMVECTOR vLength = XMVector3Length(vMove);
        float length = XMVectorGetX(vLength);

        //一定範囲内にいるかどうか
        if (length <= EP_LENGTH)
        {
            //これ以上その先へは進めなくする
            XMStoreFloat3(&transform_.position_, prevPos);

            //攻撃を行う
            eAttackS_ = true;
        }
        else
        {
            //正規化して移動量をかける
            vMove = XMVector3Normalize(vMove) * amountMove;



            //型変換
            XMStoreFloat3(&nextPos, vMove);

            //移動
            transform_.position_.x += nextPos.x;
            transform_.position_.z += nextPos.z;


        }

        //内積をもとめて角度をだしてモデルを回転させる
        XMVector3Dot(prevVec, vMove);

        /////////////////////  攻撃   //////////////////////////

        if (eAttackS_ == true)
        {
            //体当たりのようなモーション

        }



        
    }

    //ダメージを負った
    else
    {
        switch (pAcom)
        {
        case 1:
            transform_.position_.x -= nextPos.x * 45.0f;
            transform_.position_.z -= nextPos.z * 45.0f;

            isDamege = false;

            break;
        case 2:
            //後方ジャンプをさせて攻撃を受けたことを表現

            //ジャンプ前のy座標を獲得
            float checkYG = transform_.position_.y + HALF_HEIGHT;

            //y方向に向かうベクトルと平面上で移動するベクトル
            XMVECTOR vJump = XMVectorSet(0, 1, 0, 0);
            XMVECTOR vFloor = XMVectorSet(nextPos.x, 0, nextPos.z, 0);

            XMVECTOR vDamege = vJump + vFloor;
            vDamege = XMVector3Normalize(vDamege);
            vDamege *= 2.0f;

            XMFLOAT3 damege;
            XMStoreFloat3(&damege, vDamege);

            //移動(ジャンプ)
            transform_.position_.y += damege.y;
            transform_.position_.x -= damege.x * 60.0f;
            transform_.position_.z -= damege.z * 60.0f;

            //下降
            if (transform_.position_.y > checkYG)
            {
                transform_.position_.y -= 0.5f;
            }
            if (transform_.position_.y <= checkYG)
            {
                transform_.position_.y = checkYG;

                isDamege = false;
            }
            break;
        }
    }

    //移動可能範囲かどうかの判定(移動可能範囲はStageの部分のみ。Model➡ButtleField.fbx)
    moveLimit = powf(transform_.position_.x, 2.0f) + powf(transform_.position_.z, 2.0f);

    if (moveLimit > CIRCLE_RANGE)
    {
        //これ以上その先へは進めなくする
        XMStoreFloat3(&transform_.position_, prevPos);
    }
    

    //HPがなくなったら
    if (HP <= 0)
    {
        HP = MAX_HP;
        KillMe();
    }
}

//描画
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Enemy::Release()
{
    
}

//何かに当たった
void Enemy::OnCollision(GameObject* pTarget)
{
    //当たったときの処理
    //プレイヤーに当たったとき
    if (pTarget->GetObjectName() == "Player")
    {
        
        //プレイヤーの状態確認
        Player* pStatus = (Player*)FindObject("Player");
        pAttackS_ = pStatus->PGetCondition();
        if (pAttackS_ == true)
        {
            pAcom = pStatus->PGetAttack();
            //後でダメージ係数に変えて計算させる
            if (pAcom != NULL)
            {
                //攻撃の種類判別
                switch (pAcom)
                {
                //通常攻撃
                case 1:
                    HP -= 0.125f;

                    isDamege = true;

                     break;

                //強攻撃
                case 2:
                    HP -= 0.25f;

                    isDamege = true;


                    break;
                }
            }
            //pStatus->PSetFalse(pAttackS_);

        }
        SAFE_RELEASE(pStatus);
    }
}

XMFLOAT3 Enemy::GetPosition() 
{
    return transform_.position_; 
}

//敵の状態
bool Enemy::EGetCondition()
{
    return eAttackS_; 
}

void Enemy::ESetFalse(bool attackFlg_) 
{
    attackFlg_ = false;
    eAttackS_ = false;
}


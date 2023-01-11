#include "EnemyBoss.h"
#include "../../Engine/Model.h"
#include "../../Engine/Global.h"
#include "../../Engine/BoxCollider.h"

#include "../../Stage/Stage.h"
#include "Bullet.h"
#include "../../Player/Player.h"

//コンストラクタ
EnemyBoss::EnemyBoss(GameObject* parent)
    :GameObject(parent, "EnemyBoss")
{
    for (int i = 0; i < 2; i++)
    {
        hModel_[i] = -1;
    }
}

//デストラクタ
EnemyBoss::~EnemyBoss()
{
}

//初期化
void EnemyBoss::Initialize()
{
    //通常時のモデル
    hModel_[0] = Model::Load("bossNormal.fbx");
    assert(hModel_[0] >= 0);

    //被ダメージ時のモデル
    hModel_[1] = Model::Load("bossDamage.fbx");
    assert(hModel_[1] >= 0);

    //当たり判定枠
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(18, 20, 18));
    AddCollider(collision);
    
}

//更新
void EnemyBoss::Update()
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
        transform_.position_.y -= data.dist;

    }



    //HPが前回よりも低かったら
    if (HP < prevHP)
    {
        //モデルを被ダメ仕様に変更
        isDamage = true;

        //値の更新
        prevHP = HP;
    }
    else
    {
        //モデルを通常仕様に変更
        isDamage = false;
    }
    
    //体力が0になったら
    if (HP <= 0)
    {
        KillMe();
    }



    
    //ボス敵の攻撃番号の選択
    {
        if (isAttack == false)
        {

            //ランダムで攻撃を選択
            srand((unsigned int)time(NULL));    //現在時刻の情報で初期化

            int count;

            if (isSpacial == false)
            {
                count = rand() % 2 + 1;         // 1-2の間で乱数生成
            }
            else
            {
                count = rand() % 4 + 1;         // 1-4の間で乱数生成
            }
            attackNum = (State)count;           

            //攻撃フラグ、各番号の攻撃を行う

            isAttack == true;

            switch (attackNum)
            {
            default:
                isAttack = true;
                break;

            case NoAttack:
                //次の攻撃を可能にする
                isAttack = false;
                break;

            case BulletAttack:
                //弾攻撃の開始を宣言
                isBulletStart = true;
                break;

            case RotationAttack:
                //回転攻撃の開始を宣言
                isRotationStart = true;
                break;

            case WavesAttack:
                //波状攻撃の開始を宣言
                isWavesStart = true;
                break;

            case JumpAttack:
                //ジャンプ攻撃の開始を宣言
                isJumpStart = true;
                break;
            }

            
            if (HP < (MAX_HP / 10) * 3)
            {
                //特殊攻撃の開始を宣言
                isSpacial = true;
            }
        }
    }


    //////////////////　　攻撃    ///////////////////////

    //弾攻撃(攻撃番号 : 1番)
    {
        //弾攻撃が開始になっているかどうか
        if (isBulletStart == true)
        {
            //回転(90°)
            transform_.rotate_.y += 1.5f;
            isRotate = true;

            countB++;

            //2秒たったら
            if (countB >= 120)
            {
                bulletC++;

                //0.5秒ごとに弾を打つ
                if (bulletC == 30)
                {
                    //前方向
                    {
                        Bullet* pBulletF = Instantiate<Bullet>(GetParent());

                        XMFLOAT3 frontRoot;
                        XMFLOAT3 frontTip;

                        //ダメージを受けているかどうか
                        if (isDamage == false)
                        {
                            frontRoot = Model::GetBonePosition(hModel_[0], "FRONT_Root");     //根本
                            frontTip = Model::GetBonePosition(hModel_[0], "FRONT_Tip");       //先端
                        }
                        else
                        {
                            frontRoot = Model::GetBonePosition(hModel_[1], "FRONT_Root");     //根本
                            frontTip = Model::GetBonePosition(hModel_[1], "FRONT_Tip");       //先端
                        }
                        

                        XMVECTOR vFrontRoot = XMLoadFloat3(&frontRoot);
                        XMVECTOR vFrontTip = XMLoadFloat3(&frontTip);

                        XMVECTOR vFront = vFrontTip - vFrontRoot;

                        vFront = XMVector3Normalize(vFront);
                        vFront *= 0.5f;

                        XMFLOAT3 front;
                        XMStoreFloat3(&front, vFront);

                        pBulletF->SetPosition(frontTip);
                        pBulletF->SetMoveNum(front, 0);
                    }

                    //後方向
                    {
                        Bullet* pBulletB = Instantiate<Bullet>(GetParent());

                        XMFLOAT3 backRoot;
                        XMFLOAT3 backTip;

                        //ダメージを受けているかどうか
                        if (isDamage == false)
                        {
                            backRoot = Model::GetBonePosition(hModel_[0], "BACK_Root");     //根本
                            backTip = Model::GetBonePosition(hModel_[0], "BACK_Tip");       //先端
                        }
                        else
                        {
                            backRoot = Model::GetBonePosition(hModel_[1], "BACK_Root");     //根本
                            backTip = Model::GetBonePosition(hModel_[1], "BACK_Tip");       //先端
                        }


                        XMVECTOR vBackRoot = XMLoadFloat3(&backRoot);
                        XMVECTOR vBackTip = XMLoadFloat3(&backTip);

                        XMVECTOR vBack = vBackTip - vBackRoot;

                        vBack = XMVector3Normalize(vBack);
                        vBack *= 0.5f;

                        XMFLOAT3 back;
                        XMStoreFloat3(&back, vBack);

                        pBulletB->SetPosition(backTip);
                        pBulletB->SetMoveNum(back, 1);
                    }

                    //右方向
                    {
                    Bullet* pBulletR = Instantiate<Bullet>(GetParent());

                    XMFLOAT3 rightRoot;
                    XMFLOAT3 rightTip;

                    //ダメージを受けているかどうか
                    if (isDamage == false)
                    {
                        rightRoot = Model::GetBonePosition(hModel_[0], "RIGHT_Root");     //根本
                        rightTip = Model::GetBonePosition(hModel_[0], "RIGHT_Tip");       //先端
                    }
                    else
                    {
                        rightRoot = Model::GetBonePosition(hModel_[1], "RIGHT_Root");     //根本
                        rightTip = Model::GetBonePosition(hModel_[1], "RIGHT_Tip");       //先端
                    }



                    XMVECTOR vRightRoot = XMLoadFloat3(&rightRoot);
                    XMVECTOR vRightTip = XMLoadFloat3(&rightTip);

                    XMVECTOR vRight = vRightTip - vRightRoot;

                    vRight = XMVector3Normalize(vRight);
                    vRight *= 0.5f;

                    XMFLOAT3 right;
                    XMStoreFloat3(&right, vRight);


                    pBulletR->SetPosition(rightTip);
                    pBulletR->SetMoveNum(right, 2);
                    }

                    //左方向
                    {
                        Bullet* pBulletL = Instantiate<Bullet>(GetParent());

                        XMFLOAT3 leftRoot;
                        XMFLOAT3 leftTip;

                        //ダメージを受けているかどうか
                        if (isDamage == false)
                        {
                            leftRoot = Model::GetBonePosition(hModel_[0], "LEFT_Root");     //根本
                            leftTip = Model::GetBonePosition(hModel_[0], "LEFT_Tip");       //先端
                        }
                        else
                        {
                            leftRoot = Model::GetBonePosition(hModel_[1], "LEFT_Root");     //根本
                            leftTip = Model::GetBonePosition(hModel_[1], "LEFT_Tip");       //先端
                        }



                        XMVECTOR vLeftRoot = XMLoadFloat3(&leftRoot);
                        XMVECTOR vLeftTip = XMLoadFloat3(&leftTip);

                        XMVECTOR vLeft = vLeftTip - vLeftRoot;

                        vLeft = XMVector3Normalize(vLeft);
                        vLeft *= 0.5f;

                        XMFLOAT3 left;
                        XMStoreFloat3(&left, vLeft);

                        pBulletL->SetPosition(leftTip);
                        pBulletL->SetMoveNum(left, 3);
                    }

                    bulletNum++;
                    bulletC = 0;
                }

            }

            //今回の弾攻撃で出した弾の個数を確認
            //上限になったら攻撃を終わる
            if (bulletNum == 8)
            {
                bulletNum = 0;
                countB = 0;
                isRotate = false;

                //攻撃中であるという情報の破棄
                isBulletStart = false;
                attackNum = NoAttack;
            }
        }
    }

    //回転移動攻撃(渦巻上に移動して、また中心に戻ってくる)
    {

    }

    //波状攻撃(ドーナツ型で攻撃を4回行う)
    {

    }

    //ジャンプ攻撃(プレイヤーのポジションに向かって落下攻撃を3回行う。プレイヤーに当たったらプレイヤーを吹き飛ばす)
    {

    }

    //特殊攻撃(全体爆発➡プレイヤーを上空に飛ばし、全体体力の3割を奪う)
    {

    }





}

//描画
void EnemyBoss::Draw()
{
    //ダメージを受けているかどうか
    if (isDamage == false)
    {
        //受けてない時は通常モデル
        Model::SetTransform(hModel_[0], transform_);
        Model::Draw(hModel_[0]);
    }
    else
    {
        //受けているときは被ダメージモデル
        Model::SetTransform(hModel_[1], transform_);
        Model::Draw(hModel_[1]);
    }
    
}

//開放
void EnemyBoss::Release()
{
}








//何かに当たった
void EnemyBoss::OnCollision(GameObject* pTarget)
{
    //プレイヤーに当たった
    if (pTarget->GetObjectName() == "Player")
    {
        //プレイヤーの状態の取得
        Player* pStatus = (Player*)FindObject("Player");

        //攻撃しているかどうか
        bool pAttackS_ = pStatus->PGetCondition();
        if (pAttackS_ == true)
        {
            //プレイヤーの攻撃番号の取得
            int pAcom = pStatus->PGetAttack();


            //プレイヤーの攻撃の種類ごとにダメージ計算
            if (pAcom != NULL)
            {
                
                switch (pAcom)
                {
                case 1:
                    HP -= 0.0125f;
                    break;
                case 2:
                    HP -= 0.025f;
                    break;
                }
            }

        }
        SAFE_RELEASE(pStatus);

        
    }
}

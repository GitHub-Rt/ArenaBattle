#include "EnemyBoss.h"
#include "Engine/Model.h"
#include "Engine/Global.h"
#include "Engine/BoxCollider.h"

#include "Stage.h"
#include "Bullet.h"
#include "Player.h"

//コンストラクタ
EnemyBoss::EnemyBoss(GameObject* parent)
    :GameObject(parent, "EnemyBoss"), hModel_(-1)
{
}

//デストラクタ
EnemyBoss::~EnemyBoss()
{
}

//初期化
void EnemyBoss::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("boss.fbx");
    assert(hModel_ >= 0);


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
    

    
    //ボス敵の攻撃番号の選択
    {
        

        if (isAttack == false)
        {
            //ランダムで攻撃を選択
            srand((unsigned int)time(NULL));    //現在時刻の情報で初期化
            //attackNum = rand() % 3 + 1;         // 1-3の間で乱数生成


            //攻撃フラグ、各番号の攻撃を行う

            isAttack == true;

            switch (attackNum)
            {
            case 1:
                //弾攻撃の開始を宣言
                isBulletStart = true;

            }
        }
        
        if (attackNum == NULL)
        {
            //次の攻撃を可能にする
            isAttack = false;
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

                        XMFLOAT3 frontRoot = Model::GetBonePosition(hModel_, "FRONT_Root");     //根本
                        XMFLOAT3 frontTip = Model::GetBonePosition(hModel_, "FRONT_Tip");       //先端

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

                        XMFLOAT3 backRoot = Model::GetBonePosition(hModel_, "BACK_Root");     //根本
                        XMFLOAT3 backTip = Model::GetBonePosition(hModel_, "BACK_Tip");       //先端

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

                        XMFLOAT3 rightRoot = Model::GetBonePosition(hModel_, "RIGHT_Root");     //根本
                        XMFLOAT3 rightTip = Model::GetBonePosition(hModel_, "RIGHT_Tip");       //先端

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

                        XMFLOAT3 leftRoot = Model::GetBonePosition(hModel_, "LEFT_Root");     //根本
                        XMFLOAT3 leftTip = Model::GetBonePosition(hModel_, "LEFT_Tip");       //先端

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
                attackNum = NULL;   
            }
        }
    }






}

//描画
void EnemyBoss::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
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


                //プレイヤーの攻撃をリセット
                Player* pPlayer = (Player*)FindObject("Player");
                pPlayer->PSetFalse(pAttackS_);
                if (pAttackS_ == false)
                {
                    pAcom = NULL;
                }


                //体力が0になったら
                if (HP <= 0)
                {
                    KillMe();
                }

            }

        }
        SAFE_RELEASE(pStatus);

        
    }
}

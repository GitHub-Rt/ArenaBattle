#include "EnemyBoss.h"
#include "Engine/Model.h"

#include "Stage.h"
#include "Bullet.h"

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



    //////////////////　　攻撃    ///////////////////////

    countB++;
    if (countB >= 120)
    {
        bulletC++;
        if (bulletC == 30)
        {


            //前方向

            Bullet* pBulletF = Instantiate<Bullet>(this);

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
            pBulletF->SetMove(0);


            //後方向

            Bullet* pBulletB = Instantiate<Bullet>(this);

            XMFLOAT3 backRoot = Model::GetBonePosition(hModel_, "BACK_Root");     //根本
            XMFLOAT3 backTip = Model::GetBonePosition(hModel_, "BACK_Tip");       //先端

            XMVECTOR vbackRoot = XMLoadFloat3(&backRoot);
            XMVECTOR vbackTip = XMLoadFloat3(&backTip);

            XMVECTOR vback = vbackTip - vbackRoot;

            vback = XMVector3Normalize(vback);
            vback *= 0.5f;

            XMFLOAT3 back;
            XMStoreFloat3(&back, vback);

            pBulletB->SetPosition(backTip);
            pBulletB->SetMove(1);


            //右方向

            Bullet* pBulletR = Instantiate<Bullet>(this);

            XMFLOAT3 rightRoot = Model::GetBonePosition(hModel_, "RIGHT_Root");     //根本
            XMFLOAT3 rightTip = Model::GetBonePosition(hModel_, "RIGHT_Tip");       //先端

            XMVECTOR vrightRoot = XMLoadFloat3(&rightRoot);
            XMVECTOR vrightTip = XMLoadFloat3(&rightTip);

            XMVECTOR vright = vrightTip - vrightRoot;

            vright = XMVector3Normalize(vright);
            vright *= 0.5f;

            XMFLOAT3 right;
            XMStoreFloat3(&right, vright);

            pBulletR->SetPosition(rightTip);
            pBulletR->SetMove(2);


            //左方向

            Bullet* pBulletL = Instantiate<Bullet>(this);

            XMFLOAT3 leftRoot = Model::GetBonePosition(hModel_, "LEFT_Root");     //根本
            XMFLOAT3 leftTip = Model::GetBonePosition(hModel_, "LEFT_Tip");       //先端

            XMVECTOR vleftRoot = XMLoadFloat3(&leftRoot);
            XMVECTOR vleftTip = XMLoadFloat3(&leftTip);

            XMVECTOR vleft = vleftTip - vleftRoot;

            vleft = XMVector3Normalize(vleft);
            vleft *= 0.5f;

            XMFLOAT3 left;
            XMStoreFloat3(&left, vleft);

            pBulletL->SetPosition(leftTip);
            pBulletL->SetMove(3);



            //今回の弾攻撃で出した弾の個数を確認
            //上限になったら攻撃を終わる
            if (bulletNum == 7)
            {
                countB = 0;
                bulletNum = 0;
                bulletC = 0;
                isBulletEnd = true;
            }
            else
            {
                //それぞれのカウントを管理
                bulletC = 0;
                bulletNum++;
            }
        }

        
    }

    if (isBulletEnd == true && countB == 120)
    {
        //回転
        transform_.rotate_.y += 10.0f;

        isBulletEnd = false;
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
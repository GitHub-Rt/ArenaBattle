#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"


#include "EnemyBoss.h"

//コンストラクタ
Bullet::Bullet(GameObject* parent)
    :GameObject(parent, "Bullet"), hModel_(-1)
{
}

//デストラクタ
Bullet::~Bullet()
{
}

//初期化
void Bullet::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("bullet.fbx");
    assert(hModel_ >= 0);

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 3.4f, 0), 3.0f);
    AddCollider(collision);

}

//更新
void Bullet::Update()
{
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR vMove = XMLoadFloat3(&move);


    //方向ごとに進む方向を変化
    switch (disNum)
    {
    case 0:
        move.z -= 0.005f;
        break;
    case 1:
        move.z += 0.005f;
        break;
    case 2:
        move.x += 0.005f;
        break;
    case 3:
        move.x -= 0.005f;
        break;
    }

    //回転したかどうかを取得
    {
        EnemyBoss* pBoss = (EnemyBoss*)FindObject("EnemyBoss");

        //回転している
        if (pBoss->GetRotate() == true)
        {
            XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(30));  //Y軸で30°回転させる行列
            vMove = XMVector3TransformCoord(vMove, mRotateY);               //ベクトルを行列で変形
        }
    }

    
    XMStoreFloat3(&transform_.position_, vPos + vMove);


    //バトルフィールドよりも外に出たら
    if (transform_.position_.x > 60.0f || transform_.position_.x < -60.0f || transform_.position_.z > 60.0f || transform_.position_.z < -60.0f)
    {
        KillMe();
    }
}

//描画
void Bullet::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Bullet::Release()
{
}

//何かに当たった
void Bullet::OnCollision(GameObject* pTarget)
{
}
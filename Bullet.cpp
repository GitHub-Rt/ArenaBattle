#include "Bullet.h"
#include "Engine/Model.h"


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
}

//更新
void Bullet::Update()
{

    //方向ごとに進む方向を変化
    switch (disNum)
    {
    case 0:
        transform_.position_.z -= 0.5f;
        break;
    case 1:
        transform_.position_.z += 0.5f;
        break;
    case 2:
        transform_.position_.x += 0.5f;
        break;
    case 3:
        transform_.position_.x -= 0.5f;
        break;
    }


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
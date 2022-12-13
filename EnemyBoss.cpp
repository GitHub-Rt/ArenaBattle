#include "EnemyBoss.h"
#include "Engine/Model.h"

#include "Stage.h"

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
        transform_.position_.y -= (data.dist - HALF_HEIGHT);

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
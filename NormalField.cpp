#include "NormalField.h"
#include "Engine/Model.h"


//コンストラクタ
NormalField::NormalField(GameObject* parent)
    :GameObject(parent, "NormalField"), hModel_(-1)
{

}

//デストラクタ
NormalField::~NormalField()
{
}

//初期化
void NormalField::Initialize()
{
    //モデルデータのロード(床モデル)
    hModel_ = Model::Load("stage.fbx");
    assert(hModel_ >= 0);
}

//更新
void NormalField::Update()
{

}

//描画
void NormalField::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void NormalField::Release()
{
}

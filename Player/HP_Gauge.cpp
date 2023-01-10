#include "HP_Gauge.h"
#include "../Engine/Image.h"


//コンストラクタ
HP_Gauge::HP_Gauge(GameObject* parent)
    :GameObject(parent, "HP_Gauge")
{
    for (int i = 0; i < 3; i++)
    {

        hPict_[i] = -1;
    }
}

//デストラクタ
HP_Gauge::~HP_Gauge()
{
}

//初期化
void HP_Gauge::Initialize()
{
    //画像データのロード
    hPict_[0] = Image::Load("HP_GaugeFrame.jpg");
    assert(hPict_ >= 0);

    hPict_[1] = Image::Load("HP_Gauge.jpg");
    assert(hPict_ >= 0);

    hPict_[2] = Image::Load("HP_Damage.jpg");
    assert(hPict_ >= 0);
}

//更新
void HP_Gauge::Update()
{

    //ダメージを受けた
    if (isDamage )
    {

    }
}

void HP_Gauge::Draw()
{
    HPDraw(HP_Remaining);
}



//開放
void HP_Gauge::Release()
{
}


void HP_Gauge::SetDamage(int damage)
{
    Damage_amount = damage;
    isDamage = true;
}


float HP_Gauge::PercentCalc(float HP_Remaining, float Damage_amount)
{

}


void HP_Gauge::HPDraw(float HP_Remaining)
{
    //体力フレーム部分を描画
    Image::SetTransform(hPict_[0], transform_);
    Image::Draw(hPict_[0]);



    if (checkHP <= HP_Remaining)
    {
        //残りの体力部分を描画
        Image::SetTransform(hPict_[1], transform_);
        Image::Draw(hPict_[1]);
    }
    else if (checkHP < HP)
    {
        //ダメージ部分を描画
        Image::SetTransform(hPict_[2], transform_);
        Image::Draw(hPict_[2]);
    }
    checkHP++;
}
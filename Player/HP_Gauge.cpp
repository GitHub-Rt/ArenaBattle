#include "HP_Gauge.h"
#include "../Engine/Image.h"


HP_Gauge::HP_Gauge(GameObject* parent)
    :GameObject(parent, "HP_Gauge")
{
    for (int i = 0; i < 3; i++)
    {

        hPict_[i] = -1;
    }
}


HP_Gauge::~HP_Gauge()
{
}


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

void HP_Gauge::Update()
{

    //ダメージを受けた
    if (isDamage )
    {
       HP_Remaining = Calculation();
       Damage_amount = 0.0f;
    }
}

void HP_Gauge::Draw()
{
    HPDraw(HP_Remaining);
}




void HP_Gauge::Release()
{
}


void HP_Gauge::SetDamage(float damage)
{
    Damage_amount = damage;
    isDamage = true;
}


#ifdef _DEBUG
void HP_Gauge::SetHP(float HP)
{
    HP_Remaining = HP;
}

#endif

float HP_Gauge::Calculation()
{
    isDamage = false;
    return (HP_Remaining - Damage_amount);
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
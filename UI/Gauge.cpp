#include "Gauge.h"
#include "../Engine/Image.h"

//定数宣言

const float DMG_SPEED = 0.0025f;      //ダメージバーの速度
const float RCV_SPEED = 0.005f;       //回復バーの速度


Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge")
{
    for (int i = 0; i < (int)FramePict::PICT_MAX; i++)
    {
        hPict_[i] = -1;
    }

    MAX_HP = 100;

    nowHp_ = MAX_HP;      //初期HP （適宜変更）
    maxHp_ = MAX_HP;      //MaxHP（適宜変更）

    stopRatio_ = (float)nowHp_ / (float)maxHp_;
    moveRatio_ = stopRatio_;
}

Gauge::~Gauge()
{
}

void Gauge::Initialize()
{
    if (MAX_HP != 100)
    {
        nowHp_ = MAX_HP;      //初期HP （適宜変更）
        maxHp_ = MAX_HP;      //MaxHP（適宜変更）

        stopRatio_ = (float)nowHp_ / (float)maxHp_;
        moveRatio_ = stopRatio_;
    }


    //画像ファイルロード
    {
        //使用する画像ファイル名
        const char* fileName[] =
        {
            "UI/Gauge_Frame.png",
            "UI/Gauge_Green.png",
            "UI/Gauge_LightGreen.png",
            "UI/Gauge_Red.png"
        };

        //ロード
        for (int i = 0; i < (int)FramePict::PICT_MAX; i++)
        {
            hPict_[i] = Image::Load(fileName[i]);
            assert(hPict_[i] >= 0);
        }
    }
}

void Gauge::Update()
{
    //最大HPに対する、現在HPの割合
    stopRatio_ = (float)nowHp_ / (float)maxHp_;

    //バーを動かす
    if (moveRatio_ < stopRatio_) moveRatio_ += RCV_SPEED;
    if (moveRatio_ > stopRatio_) moveRatio_ -= DMG_SPEED;

}

void Gauge::Draw()
{

    Transform gaugeTrans;

    //HP変化なし
    if (abs(moveRatio_ - stopRatio_) < RCV_SPEED)
    {
        //緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[(int)FramePict::PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[(int)FramePict::PICT_GREEN]);
    }


    //回復中
    else if (moveRatio_ < stopRatio_)
    {
        //黄緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[(int)FramePict::PICT_LGREEN], gaugeTrans);
        Image::Draw(hPict_[(int)FramePict::PICT_LGREEN]);

        //緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio_;
        Image::SetTransform(hPict_[(int)FramePict::PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[(int)FramePict::PICT_GREEN]);
    }

    //ダメージ中
    else
    {
        //赤ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio_;
        Image::SetTransform(hPict_[(int)FramePict::PICT_RED], gaugeTrans);
        Image::Draw(hPict_[(int)FramePict::PICT_RED]);

        //緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[(int)FramePict::PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[(int)FramePict::PICT_GREEN]);
    }



    //枠
    gaugeTrans = transform_;
    Image::SetTransform(hPict_[(int)FramePict::PICT_FRAME], gaugeTrans);
    Image::Draw(hPict_[(int)FramePict::PICT_FRAME]);
}


void Gauge::Release()
{
}


void Gauge::Damage(float value)
{
    nowHp_ -= value;
    if (nowHp_ < 0)    nowHp_ = 0;
}


void Gauge::Recovery(float value)
{
    nowHp_ += value;
    if (nowHp_ > maxHp_) nowHp_ = maxHp_;
}
#include "PlayerGauge.h"
#include "../Character/Player.h"

const XMFLOAT3 GaugePos = XMFLOAT3(-0.95f, 0.88f, 0);
const XMFLOAT3 GaugeScale = XMFLOAT3(1.5f, 1.5f, 1.0f);

PlayerGauge::PlayerGauge(GameObject* parent)
	: HPGaugeBase(parent, "PlayerGauge")
{
    for (int i = 0; i < (int)PlayerFramePict::PICT_MAX; i++)
    {
        hPict[i] = -1;
    }
}

PlayerGauge::~PlayerGauge()
{

}

void PlayerGauge::Initialize()
{
    Player* pPlayer = (Player*)FindObject("Player");
    float hp = pPlayer->GetParameterValue(CharacterID::Player, CharacterStatus::HP);

    SetMaxHP(hp);
    SetGaugeScale(GaugeScale);
    SetGaugePosition(GaugePos.x, GaugePos.y);

    SetGaugeInformation();

    //画像ファイルロード
    {
        //使用する画像ファイル名
        const char* fileName[] =
        {
            "Gauge_Frame.png",
            "Gauge_Green.png",
            "Gauge_LightGreen.png",
            "Gauge_Red.png"
        };

        //ロード
        for (int i = 0; i < (int)PlayerFramePict::PICT_MAX; i++)
        {
            hPict[i] = GaugeImageLoad(fileName[i]);
            assert(hPict[i] >= 0);
        }
    }
}

void PlayerGauge::Draw()
{
    Transform gaugeTrans;
    float moveRatio = GetMoveRatio();
    float stopRatio = GetStopRatio();

    //HP変化なし
    if (abs(moveRatio - stopRatio) < RCV_SPEED)
    {
        //緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio;
        GaugeImageDraw(hPict[(int)PlayerFramePict::PICT_GREEN], gaugeTrans);
    }


    //回復中
    else if (moveRatio < stopRatio)
    {
        //黄緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio;
        GaugeImageDraw(hPict[(int)PlayerFramePict::PICT_LGREEN], gaugeTrans);

        //緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio;
        GaugeImageDraw(hPict[(int)PlayerFramePict::PICT_GREEN], gaugeTrans);
    }

    //ダメージ中
    else
    {
        //赤ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio;
        GaugeImageDraw(hPict[(int)PlayerFramePict::PICT_RED], gaugeTrans);

        //緑ゲージ
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio;
        GaugeImageDraw(hPict[(int)PlayerFramePict::PICT_GREEN], gaugeTrans);
    }



    //枠
    gaugeTrans = transform_;
    GaugeImageDraw(hPict[(int)PlayerFramePict::PICT_FRAME], gaugeTrans);
}
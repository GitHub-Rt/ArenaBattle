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

    //æt@C[h
    {
        //gp·éæt@C¼
        const char* fileName[] =
        {
            "Gauge_Frame.png",
            "Gauge_Green.png",
            "Gauge_LightGreen.png",
            "Gauge_Red.png"
        };

        //[h
        for (int i = 0; i < (int)PlayerFramePict::PICT_MAX; i++)
        {
            hPict[i] = UILoad(fileName[i]);
            assert(hPict[i] >= 0);
        }
    }
}

void PlayerGauge::Draw()
{
    Transform gaugeTrans;
    float moveRatio = GetMoveRatio();
    float stopRatio = GetStopRatio();

    //HPÏ»Èµ
    if (abs(moveRatio - stopRatio) < RCV_SPEED)
    {
        //ÎQ[W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio;
        UIDraw(hPict[(int)PlayerFramePict::PICT_GREEN], gaugeTrans);
    }


    //ñ
    else if (moveRatio < stopRatio)
    {
        //©ÎQ[W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio;
        UIDraw(hPict[(int)PlayerFramePict::PICT_LGREEN], gaugeTrans);

        //ÎQ[W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio;
        UIDraw(hPict[(int)PlayerFramePict::PICT_GREEN], gaugeTrans);
    }

    //_[W
    else
    {
        //ÔQ[W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio;
        UIDraw(hPict[(int)PlayerFramePict::PICT_RED], gaugeTrans);

        //ÎQ[W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio;
        UIDraw(hPict[(int)PlayerFramePict::PICT_GREEN], gaugeTrans);
    }



    //g
    gaugeTrans = transform_;
    UIDraw(hPict[(int)PlayerFramePict::PICT_FRAME], gaugeTrans);
}
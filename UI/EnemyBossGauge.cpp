#include "EnemyBossGauge.h"

const XMFLOAT3 GaugePos = XMFLOAT3(-0.95f, 1.5f, 0);
const XMFLOAT3 GaugeScale = XMFLOAT3(2.5f, 2.5f, 1.0f);
const int IMAGE_ITEMS = 3;

EnemyBossGauge::EnemyBossGauge(GameObject* parent)
    : HPGaugeBase(parent, "EnemyBossGauge")
{
    for (int i = 0; i < (int)FramePict::PICT_MAX; i++)
    {
        hPict[i] = -1;
    }
}

EnemyBossGauge::~EnemyBossGauge()
{

}

void EnemyBossGauge::Initialize()
{
    SetMaxHP(100);
    SetGaugeScale(GaugeScale);
    SetGaugePosition(GaugePos.x, GaugePos.y);
    SetGaugeInformation();

    //�摜�t�@�C�����[�h
    {
        //�g�p����摜�t�@�C����
        const char* fileName[] =
        {
            "Gauge_Frame.png",
            "Gauge_Red.png"
        };

        //���[�h
        for (int i = 0; i < IMAGE_ITEMS; i++)
        {
            hPict[i] = GaugeImageLoad(fileName[i]);
            assert(hPict[i] >= 0);
        }
    }
}

void EnemyBossGauge::Draw()
{
    Transform gaugeTrans;
    float moveRatio = GetMoveRatio();
    float stopRatio = GetStopRatio();

    //�ԃQ�[�W
    gaugeTrans = transform_;
    gaugeTrans.scale_.x *= stopRatio;
    GaugeImageDraw(hPict[(int)FramePict::PICT_RED], gaugeTrans);

    //�g
    gaugeTrans = transform_;
    GaugeImageDraw(hPict[(int)FramePict::PICT_FRAME], gaugeTrans);
}




#include "EnemyBossGauge.h"
#include "../Character/EnemyBoss.h"
const XMFLOAT3 GaugePos = XMFLOAT3(-0.9f, -0.9f, 0);
const XMFLOAT3 GaugeScale = XMFLOAT3(4.5f, 2.5f, 1.0f);

EnemyBossGauge::EnemyBossGauge(GameObject* parent)
    : HPGaugeBase(parent, "EnemyBossGauge")
{
    for (int i = 0; i < (int)BossFramePict::PICT_MAX; i++)
    {
        hPict[i] = -1;
    }
}

EnemyBossGauge::~EnemyBossGauge()
{

}

void EnemyBossGauge::Initialize()
{
    EnemyBoss* pBoss = (EnemyBoss*)FindObject("EnemyBoss");
    float hp = pBoss->GetParameterValue(CharacterID::EnemyBoss, CharacterStatus::HP);
    
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
            "Gauge_Red.png"
        };

        //ロード
        for (int i = 0; i < (int)BossFramePict::PICT_MAX; i++)
        {
            hPict[i] = UILoad(fileName[i]);
            assert(hPict[i] >= 0);
        }
    }
}

void EnemyBossGauge::Draw()
{
    Transform gaugeTrans;
    float moveRatio = GetMoveRatio();
    float stopRatio = GetStopRatio();

    //赤ゲージ
    gaugeTrans = transform_;
    gaugeTrans.scale_.x *= stopRatio;
    UIDraw(hPict[(int)BossFramePict::PICT_RED], gaugeTrans);

    //枠
    gaugeTrans = transform_;
    UIDraw(hPict[(int)BossFramePict::PICT_FRAME], gaugeTrans);
}




#pragma once
#include "HPGaugeBase.h"

//プレイヤーの体力ゲージを管理するクラス
class PlayerGauge : public HPGaugeBase
{
public:
    PlayerGauge(GameObject* parent);
    ~PlayerGauge();
    void Initialize() override;
    void Draw() override;

private:

    // 使用する画像の種類
    enum class PlayerFramePict
    {
        PICT_FRAME = 0,
        PICT_GREEN,
        PICT_LGREEN,
        PICT_RED,
        PICT_MAX
    };

    int hPict[5];
};
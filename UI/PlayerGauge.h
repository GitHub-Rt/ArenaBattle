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
    int hPict[5];
};
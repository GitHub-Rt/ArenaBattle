#pragma once
#include "HPGaugeBase.h"

class EnemyBossGauge : public HPGaugeBase
{
public:
	EnemyBossGauge(GameObject* parent);
	~EnemyBossGauge();
	void Initialize() override;
	void Draw() override;

private:
    // �g�p����摜�̎��
    enum class BossFramePict
    {
        PICT_FRAME = 0,
        PICT_RED,
        PICT_MAX
    };
	int hPict[2];
};


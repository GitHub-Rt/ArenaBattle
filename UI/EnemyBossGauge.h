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
	int hPict[2];
};


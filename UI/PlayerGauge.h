#pragma once
#include "HPGaugeBase.h"

//�v���C���[�̗̑̓Q�[�W���Ǘ�����N���X
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
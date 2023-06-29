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

    // �g�p����摜�̎��
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
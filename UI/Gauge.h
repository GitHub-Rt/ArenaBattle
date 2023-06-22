#pragma once
#include "../Engine/GameObject.h"

//�̗̓Q�[�W���Ǘ�����N���X
class Gauge : public GameObject
{
public:
    Gauge(GameObject* parent);
    ~Gauge();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    ////////////////////////////////////////

    //�_���[�W���󂯂�
    //�����Fvalue  �_���[�W��
    void Damage(float value);

    //��
    //�����Fvalue  �񕜗�
    void Recovery(float value);


    void SetGaugePosition(XMFLOAT3 pos) { transform_.position_ = pos; }
    void SetGaugeScale(XMFLOAT3 scale) { transform_.scale_ = scale; }


private:
    float nowHp_; //���݂̂g�o
    float maxHp_; //�ő�g�o


    float stopRatio_;       //�ő�HP�ɑ΂���Œ肳�ꂽ�Q�[�W�̊���
    float moveRatio_;       //�ő�HP�ɑ΂���ω����Ă�Q�[�W�̊���



    //�g�p����摜�̎��
    enum class FramePict
    {
        PICT_FRAME = 0,
        PICT_GREEN,
        PICT_LGREEN,
        PICT_RED,
        PICT_MAX
    };

    //�摜�ԍ�
    int hPict_[5];


};
#include "Gauge.h"
#include "../Engine/Image.h"

//�萔�錾

const float DMG_SPEED = 0.0025f;      //�_���[�W�o�[�̑��x
const float RCV_SPEED = 0.005f;       //�񕜃o�[�̑��x


Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge")
{
    for (int i = 0; i < (int)FramePict::PICT_MAX; i++)
    {
        hPict_[i] = -1;
    }

    MAX_HP = 100;

    nowHp_ = MAX_HP;      //����HP �i�K�X�ύX�j
    maxHp_ = MAX_HP;      //MaxHP�i�K�X�ύX�j

    stopRatio_ = (float)nowHp_ / (float)maxHp_;
    moveRatio_ = stopRatio_;
}

Gauge::~Gauge()
{
}

void Gauge::Initialize()
{
    if (MAX_HP != 100)
    {
        nowHp_ = MAX_HP;      //����HP �i�K�X�ύX�j
        maxHp_ = MAX_HP;      //MaxHP�i�K�X�ύX�j

        stopRatio_ = (float)nowHp_ / (float)maxHp_;
        moveRatio_ = stopRatio_;
    }


    //�摜�t�@�C�����[�h
    {
        //�g�p����摜�t�@�C����
        const char* fileName[] =
        {
            "UI/Gauge_Frame.png",
            "UI/Gauge_Green.png",
            "UI/Gauge_LightGreen.png",
            "UI/Gauge_Red.png"
        };

        //���[�h
        for (int i = 0; i < (int)FramePict::PICT_MAX; i++)
        {
            hPict_[i] = Image::Load(fileName[i]);
            assert(hPict_[i] >= 0);
        }
    }
}

void Gauge::Update()
{
    //�ő�HP�ɑ΂���A����HP�̊���
    stopRatio_ = (float)nowHp_ / (float)maxHp_;

    //�o�[�𓮂���
    if (moveRatio_ < stopRatio_) moveRatio_ += RCV_SPEED;
    if (moveRatio_ > stopRatio_) moveRatio_ -= DMG_SPEED;

}

void Gauge::Draw()
{

    Transform gaugeTrans;

    //HP�ω��Ȃ�
    if (abs(moveRatio_ - stopRatio_) < RCV_SPEED)
    {
        //�΃Q�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[(int)FramePict::PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[(int)FramePict::PICT_GREEN]);
    }


    //�񕜒�
    else if (moveRatio_ < stopRatio_)
    {
        //���΃Q�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[(int)FramePict::PICT_LGREEN], gaugeTrans);
        Image::Draw(hPict_[(int)FramePict::PICT_LGREEN]);

        //�΃Q�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio_;
        Image::SetTransform(hPict_[(int)FramePict::PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[(int)FramePict::PICT_GREEN]);
    }

    //�_���[�W��
    else
    {
        //�ԃQ�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio_;
        Image::SetTransform(hPict_[(int)FramePict::PICT_RED], gaugeTrans);
        Image::Draw(hPict_[(int)FramePict::PICT_RED]);

        //�΃Q�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[(int)FramePict::PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[(int)FramePict::PICT_GREEN]);
    }



    //�g
    gaugeTrans = transform_;
    Image::SetTransform(hPict_[(int)FramePict::PICT_FRAME], gaugeTrans);
    Image::Draw(hPict_[(int)FramePict::PICT_FRAME]);
}


void Gauge::Release()
{
}


void Gauge::Damage(float value)
{
    nowHp_ -= value;
    if (nowHp_ < 0)    nowHp_ = 0;
}


void Gauge::Recovery(float value)
{
    nowHp_ += value;
    if (nowHp_ > maxHp_) nowHp_ = maxHp_;
}
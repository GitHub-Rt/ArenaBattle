#include "Warning.h"
#include "../Engine/Easing.h"

const int ALPHA = 255;              //�����x�v�Z
const int BACK_PICT_ALPHA = 128;    //�w�i�����̃A���t�@�l

Warning::Warning(GameObject* parent)
	: UIBase(parent, "Warning")
{
    hPict = -1;
    hPictBack = -1;
    alphaTimer = 0;
    keepTimer = 0;
    isGain = false;
    alpha = 0;
}

Warning::~Warning()
{

}

void Warning::Initialize()
{
    hPict = UILoad("Warning.png");
    hPictBack = UILoad("WarningBack.png");

    UIAlpha(hPict, alpha * ALPHA);
    UIAlpha(hPictBack, BACK_PICT_ALPHA);
}

void Warning::UIUpdate()
{
    const int MAX_TIMER = 10;   //�����ɂ��邩�s�����ɂ��邩���؂�ւ��܂ł̎���

    alphaTimer++;
    if (alphaTimer == MAX_TIMER)
    {
        alphaTimer = 0;
        ChangeAlpha();
        UIAlpha(hPict, alpha * ALPHA);
    }
}

void Warning::Draw()
{
    // �w�i
    UIDraw(hPictBack, transform_);

    // �e�L�X�g
    UIDraw(hPict, transform_);
}

void Warning::ChangeAlpha()
{
    const int MAX_KEEP_TIMER = 5;       //�s�����ɂȂ������̍ő厝������
    const int MAX_ALPHA = 1;            //�s�����x�̍ő�l
    const float CHANGE_ALPHA = 0.25f;   //�A���t�@�l�̕ω���

    if (isGain)
    {//�������s�����ɂ��Ă���

        alpha += CHANGE_ALPHA;

        if (alpha >= MAX_ALPHA)
        {
            keepTimer++;
            if (keepTimer == MAX_KEEP_TIMER)
            {
                keepTimer = 0;
                isGain = false;
            }
            alpha = MAX_ALPHA;
        }
    }
    else
    {//�����������ɂ��Ă���

        alpha -= CHANGE_ALPHA;

        if (alpha <= 0)
        {
            isGain = true;
            alpha = 0;
        }
    }
}
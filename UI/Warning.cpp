#include "Warning.h"
#include "../Engine/Easing.h"

const float BACK_PICT_ALPHA = 0.5;    //�w�i�����̃A���t�@�l

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

    UIAlpha(hPict, alpha);
    UIAlpha(hPictBack, BACK_PICT_ALPHA);
}

void Warning::UIUpdate()
{
    const int MAX_TIMER = 10;           //�����ɂ��邩�s�����ɂ��邩���؂�ւ��܂ł̎���
    const int MAX_ALPHA = 1;            //�s�����x�̍ő�l
    const int MAX_KEEP_TIMER = 5;       //�s�����ɂȂ������̍ő厝������

    // �摜�̓����x��ω�����������
    alphaTimer++;
    if (alphaTimer == MAX_TIMER)
    {
        alphaTimer = 0;
        if (isGain)
        {
            // �����x�������鏈��
            alpha = UIChangeAlphaUp(alpha);

            // �ő�l�ȏ�ɂȂ����班���̊Ԃ��̓����x��ۂ�
            if (alpha >= MAX_ALPHA)
            {
                keepTimer++;

                // ��莞�Ԍo�ߌ㓧���x�������鏈���Ɉڍs����
                if (keepTimer == MAX_KEEP_TIMER)
                {
                    keepTimer = 0;
                    isGain = false;
                }
            }
        }
        else
        {
            // �����x�������鏈��
            alpha = UIChangeAlphaDawn(alpha);

            // �Œ�̓����x���Ⴍ�Ȃ����炠���鏈���Ɉڍs����
            if (alpha <= 0)
            {
                isGain = true;
            }
        }
        
        UIAlpha(hPict, alpha);
    }
}

void Warning::Draw()
{
    // �w�i
    UIDraw(hPictBack, transform_);

    // �e�L�X�g
    UIDraw(hPict, transform_);
}
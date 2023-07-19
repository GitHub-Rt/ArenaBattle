#include "Warning.h"
#include "../Engine/Easing.h"

const int ALPHA = 255;              //透明度計算
const int BACK_PICT_ALPHA = 128;    //背景部分のアルファ値

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
    const int MAX_TIMER = 10;   //透明にするか不透明にするかが切り替わるまでの時間

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
    // 背景
    UIDraw(hPictBack, transform_);

    // テキスト
    UIDraw(hPict, transform_);
}

void Warning::ChangeAlpha()
{
    const int MAX_KEEP_TIMER = 5;       //不透明になった時の最大持続時間
    const int MAX_ALPHA = 1;            //不透明度の最大値
    const float CHANGE_ALPHA = 0.25f;   //アルファ値の変化量

    if (isGain)
    {//少しずつ不透明にしていく

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
    {//少しずつ透明にしていく

        alpha -= CHANGE_ALPHA;

        if (alpha <= 0)
        {
            isGain = true;
            alpha = 0;
        }
    }
}
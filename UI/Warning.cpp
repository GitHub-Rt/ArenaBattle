#include "Warning.h"
#include "../Engine/Easing.h"

const float BACK_PICT_ALPHA = 0.5;    //背景部分のアルファ値

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
    const int MAX_TIMER = 10;           //透明にするか不透明にするかが切り替わるまでの時間
    const int MAX_ALPHA = 1;            //不透明度の最大値
    const int MAX_KEEP_TIMER = 5;       //不透明になった時の最大持続時間

    // 画像の透明度を変化させ続ける
    alphaTimer++;
    if (alphaTimer == MAX_TIMER)
    {
        alphaTimer = 0;
        if (isGain)
        {
            // 透明度をあげる処理
            alpha = UIChangeAlphaUp(alpha);

            // 最大値以上になったら少しの間その透明度を保つ
            if (alpha >= MAX_ALPHA)
            {
                keepTimer++;

                // 一定時間経過後透明度を下げる処理に移行する
                if (keepTimer == MAX_KEEP_TIMER)
                {
                    keepTimer = 0;
                    isGain = false;
                }
            }
        }
        else
        {
            // 透明度を下げる処理
            alpha = UIChangeAlphaDawn(alpha);

            // 最低の透明度より低くなったらあげる処理に移行する
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
    // 背景
    UIDraw(hPictBack, transform_);

    // テキスト
    UIDraw(hPict, transform_);
}
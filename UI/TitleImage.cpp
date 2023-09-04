#include "TitleImage.h"

#include "../Engine/Easing.h"

TitleImage::TitleImage(GameObject* parent)
	: UIBase(parent, "TitleImage")
{
	hPict = -1;
	alpha = 0;
	ease = 0;
}

TitleImage::~TitleImage()
{

}

void TitleImage::Initialize()
{
	hPict = UILoad("GameTitle.png");
	UIAlpha(hPict, 0);
}

void TitleImage::UIUpdate()
{
	const float EASING_STEP = 0.005f;	//変化量

	//透明度が最大値じゃない間透明度を上げ続ける
	if (alpha != 1)
	{
		alpha = Easing::EaseInQuad(ease);
		UIAlpha(hPict, alpha);

		ease += EASING_STEP;
		
		// 最大値を超えないようにする
		if (ease >= 1)
		{
			ease = 1;
		}
	}
}

void TitleImage::Draw()
{
	UIDraw(hPict, transform_);
}

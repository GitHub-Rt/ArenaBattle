#include "DefeatImage.h"
#include "../Engine/Easing.h"

DefeatImage::DefeatImage(GameObject* parent)
	: UIBase(parent, "DefeatImage")
{
	hPict = -1;
}

DefeatImage::~DefeatImage()
{

}

void DefeatImage::Initialize()
{
	hPict = UILoad("Dead.png");
	UIAlpha(hPict, 0);
}

void DefeatImage::UIUpdate()
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

void DefeatImage::Draw()
{
	UIDraw(hPict, transform_);
}


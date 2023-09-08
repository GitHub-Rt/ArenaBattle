#include "VictoryImage.h"
#include "../Engine/Easing.h"

VictoryImage::VictoryImage(GameObject* parent)
	: UIBase(parent, "VictoryImage")
{
	hPict = -1;
}

VictoryImage::~VictoryImage()
{

}

void VictoryImage::Initialize()
{
	hPict = UILoad("Victory.png");
	UIAlpha(hPict, 0);
}

void VictoryImage::UIUpdate()
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

void VictoryImage::Draw()
{
	UIDraw(hPict, transform_);
}
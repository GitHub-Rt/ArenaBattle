#include "UIBase.h"
#include "../Engine/Image.h"

UIBase::UIBase(GameObject* parent, std::string fileName)
	: GameObject(parent, fileName)
{

}

UIBase::~UIBase()
{

}

int UIBase::UILoad(std::string fileName)
{
	int hPict = Image::Load("UI/" + fileName);
	assert(hPict >= 0);

	return hPict;
}

void UIBase::UIDraw(int handle, Transform trans)
{
	Image::SetTransform(handle, trans);
	Image::Draw(handle);
}

void UIBase::Update()
{
	UIUpdate();
}

void UIBase::UIRect(RectUI target,int handle, int num)
{
	switch (target)
	{
	case RectUI::RecoveryNumber:
		Image::SetRect(handle, num * 150, 0, 150, 256);
		break;
	default:
		break;
	}
}

void UIBase::UIAlpha(int handle, float alpha)
{
	const int ALPHA = 255;              //透明度計算

	Image::SetAlpha(handle, alpha * ALPHA);
}

float UIBase::UIChangeAlphaUp(float alpha)
{
	const int MAX_ALPHA = 1;            //不透明度の最大値
	const float CHANGE_ALPHA = 0.25f;   //アルファ値の変化量

	alpha += CHANGE_ALPHA;
	if (alpha >= MAX_ALPHA)
	{
		alpha = MAX_ALPHA;
	}

	return alpha;
}

float UIBase::UIChangeAlphaDawn(float alpha)
{
	const float CHANGE_ALPHA = 0.25f;   //アルファ値の変化量

	alpha -= CHANGE_ALPHA;
	if (alpha <= 0)
	{
		alpha = 0;
	}

	return alpha;
}

void UIBase::Release()
{

}
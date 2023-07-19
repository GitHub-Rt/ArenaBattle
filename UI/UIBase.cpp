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

void UIBase::Release()
{

}
#include "DefeatImage.h"

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
}

void DefeatImage::UIUpdate()
{

}

void DefeatImage::Draw()
{
	UIDraw(hPict, transform_);
}


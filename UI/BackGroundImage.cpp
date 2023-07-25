#include "BackGroundImage.h"

BackGroundImage::BackGroundImage(GameObject* parent)
	: UIBase(parent, "BackGroundImage")
{
	hPict = -1;
}

BackGroundImage::~BackGroundImage()
{

}

void BackGroundImage::Initialize()
{
	hPict = UILoad("BackGroundImage.jpg");
}

void BackGroundImage::Draw()
{
	UIDraw(hPict, transform_);
}
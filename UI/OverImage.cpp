#include "OverImage.h"

OverImage::OverImage(GameObject* parent)
	: UIBase(parent, "OverImage")
{
	hPict = -1;
}

OverImage::~OverImage()
{

}

void OverImage::Initialize()
{
	hPict = UILoad("GameOver.png");
}

void OverImage::UIUpdate()
{

}

void OverImage::Draw()
{
	UIDraw(hPict, transform_);
}
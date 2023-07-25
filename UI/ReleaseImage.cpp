#include "ReleaseImage.h"

ReleaseImage::ReleaseImage(GameObject* parent)
	: UIBase(parent, "ReleaseImage")
{
	hPict = -1;
}

ReleaseImage::~ReleaseImage()
{

}

void ReleaseImage::Initialize()
{
	hPict = UILoad("Release.png");
}

void ReleaseImage::UIUpdate()
{

}

void ReleaseImage::Draw()
{
	UIDraw(hPict, transform_);
}
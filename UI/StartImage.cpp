#include "StartImage.h"

StartImage::StartImage(GameObject* parent)
	: UIBase(parent, "StartImage")
{
	hPict = -1;
}

StartImage::~StartImage()
{

}

void StartImage::Initialize()
{
	hPict = UILoad("Start.png");
}

void StartImage::UIUpdate()
{

}

void StartImage::Draw()
{
	UIDraw(hPict, transform_);
}
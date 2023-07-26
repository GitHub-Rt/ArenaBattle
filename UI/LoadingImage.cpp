#include "LoadingImage.h"

LoadingImage::LoadingImage(GameObject* parent)
	: UIBase(parent, "LoadingImage")
{
	hPict = -1;
}

LoadingImage::~LoadingImage()
{

}

void LoadingImage::Initialize()
{
	hPict = UILoad("Load.jpg");
}

void LoadingImage::UIUpdate()
{

}

void LoadingImage::Draw()
{
	UIDraw(hPict, transform_);
}
#include "RetryImage.h"

RetryImage::RetryImage(GameObject* parent)
	: UIBase(parent, "RetryImage")
{
	hPict = -1;
}

RetryImage::~RetryImage()
{

}

void RetryImage::Initialize()
{
	hPict = UILoad("Retry.png");
}

void RetryImage::UIUpdate()
{

}

void RetryImage::Draw()
{
	UIDraw(hPict, transform_);
}
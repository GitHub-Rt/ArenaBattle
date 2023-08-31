#include "PauseImage.h"

PauseImage::PauseImage(GameObject* parent)
	: UIBase(parent, "PauseImage")
{
	hPict = -1;
}

PauseImage::~PauseImage()
{

}

void PauseImage::Initialize()
{
	hPict = UILoad("Pause.png");
}

void PauseImage::UIUpdate()
{

}

void PauseImage::Draw()
{
	UIDraw(hPict, transform_);
}
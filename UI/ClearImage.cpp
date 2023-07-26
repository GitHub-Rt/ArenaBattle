#include "ClearImage.h"

ClearImage::ClearImage(GameObject* parent)
	: UIBase(parent, "ClearImage")
{
	hPict = -1;
}

ClearImage::~ClearImage()
{

}

void ClearImage::Initialize()
{
	hPict = UILoad("GameClear.png");
}

void ClearImage::UIUpdate()
{

}

void ClearImage::Draw()
{
	UIDraw(hPict, transform_);
}
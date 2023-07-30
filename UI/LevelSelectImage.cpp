#include "LevelSelectImage.h"

LevelSelectImage::LevelSelectImage(GameObject* parent)
	: UIBase(parent, "LevelSelectImage")
{
	hPict = -1;
}

LevelSelectImage::~LevelSelectImage()
{

}

void LevelSelectImage::Initialize()
{
	hPict = UILoad("LevelSelectImage.png");
}

void LevelSelectImage::Draw()
{
	UIDraw(hPict, transform_);
}
#include "VictoryImage.h"

VictoryImage::VictoryImage(GameObject* parent)
	: UIBase(parent, "VictoryImage")
{
	hPict = -1;
}

VictoryImage::~VictoryImage()
{

}

void VictoryImage::Initialize()
{
	hPict = UILoad("Victory.png");
}

void VictoryImage::UIUpdate()
{

}

void VictoryImage::Draw()
{
	UIDraw(hPict, transform_);
}
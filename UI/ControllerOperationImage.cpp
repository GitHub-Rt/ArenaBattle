#include "ControllerOperationImage.h"

ControllerOperationImage::ControllerOperationImage(GameObject* parent)
	: UIBase(parent, "ControllerOperationImage")
{
	hPict = -1;
}

ControllerOperationImage::~ControllerOperationImage()
{

}

void ControllerOperationImage::Initialize()
{
	hPict = UILoad("ControllerOperationImage.png");
}

void ControllerOperationImage::UIUpdate()
{

}

void ControllerOperationImage::Draw()
{
	UIDraw(hPict, transform_);
}
#include "KeyboardOperationImage.h"

KeyboardOperationImage::KeyboardOperationImage(GameObject* parent)
	: UIBase(parent, "KeyboardOperationImage")
{
	hPict = -1;
}

KeyboardOperationImage::~KeyboardOperationImage()
{

}

void KeyboardOperationImage::Initialize()
{
	hPict = UILoad("KeyboardOperationImage.png");
}

void KeyboardOperationImage::UIUpdate()
{

}

void KeyboardOperationImage::Draw()
{
	UIDraw(hPict, transform_);
}
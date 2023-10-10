#include "HowToPlayImage.h"
#include "../Engine/Input.h"


HowToPlayImage::HowToPlayImage(GameObject* parent)
	: UIBase(parent, "HowToPlayImage")
{
	hPict = -1;
	hPress = -1;
}

HowToPlayImage::~HowToPlayImage()
{

}

void HowToPlayImage::Initialize()
{
	hPict = UILoad("howToPlay.png");

	if (Input::IsControllerConnected())
	{
		hPress = UILoad("controllerPress.png");
	}
	else
	{
		hPress = UILoad("keyboardPress.png");
	}
}

void HowToPlayImage::UIUpdate()
{
	
}

void HowToPlayImage::Draw()
{
	UIDraw(hPict, transform_);
	UIDraw(hPress, transform_);
}


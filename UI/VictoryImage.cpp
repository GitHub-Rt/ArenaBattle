#include "VictoryImage.h"
#include "../Engine/Easing.h"

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
	UIAlpha(hPict, 0);
}

void VictoryImage::UIUpdate()
{
	const float EASING_STEP = 0.005f;	//�ω���

	//�����x���ő�l����Ȃ��ԓ����x���グ������
	if (alpha != 1)
	{
		alpha = Easing::EaseInQuad(ease);
		UIAlpha(hPict, alpha);

		ease += EASING_STEP;

		// �ő�l�𒴂��Ȃ��悤�ɂ���
		if (ease >= 1)
		{
			ease = 1;
		}
	}
}

void VictoryImage::Draw()
{
	UIDraw(hPict, transform_);
}
#include "DefeatImage.h"
#include "../Engine/Easing.h"

DefeatImage::DefeatImage(GameObject* parent)
	: UIBase(parent, "DefeatImage")
{
	hPict = -1;
}

DefeatImage::~DefeatImage()
{

}

void DefeatImage::Initialize()
{
	hPict = UILoad("Dead.png");
	UIAlpha(hPict, 0);
}

void DefeatImage::UIUpdate()
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

void DefeatImage::Draw()
{
	UIDraw(hPict, transform_);
}


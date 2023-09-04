#include "TitleImage.h"

#include "../Engine/Easing.h"

TitleImage::TitleImage(GameObject* parent)
	: UIBase(parent, "TitleImage")
{
	hPict = -1;
	alpha = 0;
	ease = 0;
}

TitleImage::~TitleImage()
{

}

void TitleImage::Initialize()
{
	hPict = UILoad("GameTitle.png");
	UIAlpha(hPict, 0);
}

void TitleImage::UIUpdate()
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

void TitleImage::Draw()
{
	UIDraw(hPict, transform_);
}

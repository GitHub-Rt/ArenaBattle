#include "SelectBox.h"


SelectBox::SelectBox(GameObject* parent)
	: UIBase(parent, "SelectBoxf")
{
	hPict = -1;
}

SelectBox::~SelectBox()
{

}

void SelectBox::Initialize()
{
	hPict = UILoad("SelectBox.png");
}

void SelectBox::UIUpdate()
{

}

void SelectBox::Draw()
{
	UIDraw(hPict, transform_);
}

void SelectBox::SetSelectBox(XMFLOAT3 pos, bool isScaleXChange)
{
	const float CHANGE_SCALE_X = 1.55f;
	const float NORMAL_SCALE_X = 1.25f;

	// 拡大が必要かどうか
	if (isScaleXChange)
	{
		transform_.scale_.x = CHANGE_SCALE_X;
	}
	else
	{
		transform_.scale_.x = NORMAL_SCALE_X;
	}

	// ポジションをセットする
	transform_.position_ = pos;
}
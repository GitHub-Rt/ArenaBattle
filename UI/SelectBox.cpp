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
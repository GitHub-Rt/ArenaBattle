#include "RecorveryNumber.h"
#include "RecoveryPotion.h"

const XMFLOAT3 POSION_SCAL = { 0.35f, 0.35f, 1.0f };
const XMFLOAT3 POSION_POS = { -0.88f, 0.68f, 0 };

RecorveryNumber::RecorveryNumber(GameObject* parent)
	: UIBase(parent, "RecorveryNumber")
{
	hPict = -1;
	number = 0;
	pPotion = nullptr;
}

RecorveryNumber::~RecorveryNumber()
{

}

void RecorveryNumber::Initialize()
{
	hPict = UILoad("PotionCount.png");
	pPotion = (RecoveryPotion*)FindObject("RecoveryPotion");

	transform_.scale_ = POSION_SCAL;
	transform_.position_ = POSION_POS;

	
}

void RecorveryNumber::UIUpdate()
{
	if (pPotion != nullptr)
	{
		if (pPotion->GetPotionCount() != number)
		{
			number--;
			UIRect(RectUI::RecoveryNumber, hPict, number);
		}
	}
	else
	{
		KillMe();
	}
}

void RecorveryNumber::Draw()
{
	UIDraw(hPict, transform_);
}
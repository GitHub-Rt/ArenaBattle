#include "RecoveryPotion.h"
#include "RecorveryNumber.h"

const XMFLOAT3 POSION_SCAL = { 1.05f, 1.05f, 1.0f };
const XMFLOAT3 POSION_POS = { -0.91f, 0.76f, 0 };



RecoveryPotion::RecoveryPotion(GameObject* parent)
	: UIBase(parent, "RecoveryPotion")
{
	hPict = -1;
	potionNumber = 0;
	pNumber = nullptr;
}

RecoveryPotion::~RecoveryPotion()
{

}

void RecoveryPotion::Initialize()
{
	hPict = UILoad("Potion.png");

	transform_.scale_ = POSION_SCAL;
	transform_.position_ = POSION_POS;
}

void RecoveryPotion::Draw()
{
	UIDraw(hPict, transform_);
}

void RecoveryPotion::DawnPotionNumber()
{
	potionNumber--;
}

void RecoveryPotion::SetPotionCount(int num)
{
	potionNumber = num;

	pNumber = Instantiate<RecorveryNumber>(this);
	pNumber->SetPotionCount(potionNumber);
}


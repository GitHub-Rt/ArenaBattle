#pragma once
#include "UIBase.h"

class RecoveryPotion;

class RecorveryNumber : public UIBase
{
public:
	RecorveryNumber(GameObject* parent);
	~RecorveryNumber();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

	void SetPotionCount(int num) 
	{
		number = num;
		UIRect(RectUI::RecoveryNumber, hPict, number);
	}

private:
	int hPict;
	int number;
	RecoveryPotion* pPotion;
};


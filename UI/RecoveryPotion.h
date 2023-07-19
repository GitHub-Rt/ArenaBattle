#pragma once
#include "UIBase.h"

class RecorveryNumber;

class RecoveryPotion : public UIBase
{
public:
	RecoveryPotion(GameObject* parent);
	~RecoveryPotion();
	void Initialize() override;
	void Draw() override;

	void DawnPotionNumber();

	int GetPotionCount() { return potionNumber; }
	void SetPotionCount(int num);

private:
	int hPict;
	int potionNumber;
	RecorveryNumber* pNumber;
};


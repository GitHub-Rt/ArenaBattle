#pragma once
#include "StageBase.h"

class BattleBackGround : public StageBase
{
public:

	BattleBackGround(GameObject* parent);
	~BattleBackGround();
	void Initialize() override;
	void Draw() override;
};


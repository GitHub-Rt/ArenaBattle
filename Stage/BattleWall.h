#pragma once
#include "StageBase.h"

class BattleWall : public StageBase
{
public:
	BattleWall(GameObject* parent);
	~BattleWall();
	void Initialize()  override;
};


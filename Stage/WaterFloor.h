#pragma once
#include "StageBase.h"

class WaterFloor : public StageBase
{
public:

	WaterFloor(GameObject* parent);
	~WaterFloor();
	void Initialize() override;
	void Draw() override;

};


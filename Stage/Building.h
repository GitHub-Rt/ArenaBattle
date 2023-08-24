#pragma once
#include "StageBase.h"

class Building : public StageBase
{
public:
	
	Building(GameObject* parent);
	~Building();
	void Initialize() override;
	void Draw() override;
};


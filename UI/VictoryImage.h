#pragma once
#include "UIBase.h"

class VictoryImage : public UIBase
{

public:

	VictoryImage(GameObject* parent);
	~VictoryImage();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

private:

	int hPict;

};


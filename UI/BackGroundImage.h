#pragma once
#include "UIBase.h"

class BackGroundImage : public UIBase
{
public:
	BackGroundImage(GameObject* parent);
	~BackGroundImage();
	void Initialize() override;
	void Draw() override;

	void UIUpdate() override {};

private:
	int hPict;
};


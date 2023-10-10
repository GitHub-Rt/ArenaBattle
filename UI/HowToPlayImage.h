#pragma once
#include "UIBase.h"

class HowToPlayImage : public UIBase
{
public:
	
	HowToPlayImage(GameObject* parent);
	~HowToPlayImage();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

private:

	int hPict;
	int hPress;

};


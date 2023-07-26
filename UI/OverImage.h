#pragma once
#include "UIBase.h"

class OverImage : public UIBase
{
public:

	OverImage(GameObject* parent);
	~OverImage();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;
	
private:

	int hPict;

};


#pragma once
#include "UIBase.h"

class DefeatImage : public UIBase
{

public:

	DefeatImage(GameObject* parent);
	~DefeatImage();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

private:

	int hPict;

};


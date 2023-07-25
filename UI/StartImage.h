#pragma once
#include "UIBase.h"

class StartImage : public UIBase
{
public:

	StartImage(GameObject* parent);
	~StartImage();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

private:

	int hPict;

};


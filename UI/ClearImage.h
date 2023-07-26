#pragma once
#include "UIBase.h"

class ClearImage : public UIBase
{
public:

	ClearImage(GameObject* parent);
	~ClearImage();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

private:

	int hPict;

};


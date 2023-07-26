#pragma once
#include "UIBase.h"

class KeyboardOperationImage : public UIBase
{
public:

	KeyboardOperationImage(GameObject* parent);
	~KeyboardOperationImage();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

private:

	int hPict;

};


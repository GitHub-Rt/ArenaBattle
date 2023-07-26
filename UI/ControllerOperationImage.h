#pragma once
#include "UIBase.h"

class ControllerOperationImage : public UIBase
{
public:

	ControllerOperationImage(GameObject* parent);
	~ControllerOperationImage();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

private:

	int hPict;

};


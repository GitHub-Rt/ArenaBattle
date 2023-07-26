#pragma once
#include "UIBase.h"

class RetryImage : public UIBase
{
public:

	RetryImage(GameObject* parent);
	~RetryImage();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

private:

	int hPict;

};


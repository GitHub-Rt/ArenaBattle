#pragma once
#include "UIBase.h"

class PauseImage : public UIBase
{
public:

	PauseImage(GameObject* parent);
	~PauseImage();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

private:

	int hPict;

};


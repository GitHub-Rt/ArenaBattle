#pragma once
#include "UIBase.h"

class ReleaseImage : public UIBase
{
public:

	ReleaseImage(GameObject* parent);
	~ReleaseImage();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

private:

	int hPict;
	
};


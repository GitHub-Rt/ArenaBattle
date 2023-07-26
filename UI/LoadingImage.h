#pragma once
#include "UIBase.h"

class LoadingImage : public UIBase
{
public:

	LoadingImage(GameObject* parent);
	~LoadingImage();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;
	
private:

	int hPict;

};


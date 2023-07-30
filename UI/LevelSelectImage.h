#pragma once
#include "UIBase.h"

class LevelSelectImage : public UIBase
{
public:

	LevelSelectImage(GameObject* parent);
	~LevelSelectImage();
	void Initialize() override;
	void UIUpdate() override {}
	void Draw() override;

private:

	int hPict;

};


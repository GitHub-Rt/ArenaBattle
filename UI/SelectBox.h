#pragma once
#include "UIBase.h"

class SelectBox : public UIBase
{
public:

	SelectBox(GameObject* parent);
	~SelectBox();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

	void SetBoxPosition(XMFLOAT3 pos) { transform_.position_ = pos; }
		
private:

	int hPict;
};


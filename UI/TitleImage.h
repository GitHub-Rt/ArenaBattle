#pragma once
#include "UIBase.h"
class TitleImage : public UIBase
{
public:
	
	TitleImage(GameObject* parent);
	~TitleImage();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

	// 透明度を最大値にする
	void SetMaxAlpha() 
	{
		alpha = 1; 
		UIAlpha(hPict, alpha);
	}

	float GetAlpha() { return alpha; }

private:

	int hPict;
	float alpha;
	float ease;
};


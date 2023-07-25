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

	// “§–¾“x‚ğÅ‘å’l‚É‚·‚é
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


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
		
	/// <summary>
	/// セレクトボックスのポジションをセットする関数
	/// </summary>
	/// <param name="pos">ポジション</param>
	/// <param name="isScaleXChange">xを拡大するかどうか</param>
	void SetSelectBox(XMFLOAT3 pos, bool isScaleXChange = false);

private:

	int hPict;
};


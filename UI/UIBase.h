#pragma once
#include "../Engine/GameObject.h"

enum class RectUI
{
	RecoveryNumber,
};

class UIBase : public GameObject
{
public:
	UIBase(GameObject* parent, std::string fileName);
	~UIBase();
	int UILoad(std::string fileName);
	void Update() override;
	void UIDraw(int handle, Transform trans);
	void Release() override;

	// 画像の切り抜きが必要な時に呼ぶ関数
	void UIRect(RectUI target,int handle, int num = 0);

	// UIの透明度
	void UIAlpha(int handle, int alpha);

	// 更新処理が必要なUIのみ呼ばれる
	virtual void UIUpdate() {}
};


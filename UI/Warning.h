#pragma once
#include "UIBase.h"

class Warning : public UIBase
{
public:
	Warning(GameObject* parent);
	~Warning();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

	// 透明度を変更する関数
	void ChangeAlpha();

private:
	int hPict;          //テキスト画像
	int hPictBack;      //背景画像
	int alphaTimer;     //透明度を管理するタイマー
	int keepTimer;      //状態を持続させる時間計測タイマー
	bool isGain;        //透明度が上がっているかどうか
	float alpha;        //テキスト透明度
};


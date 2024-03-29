#pragma once
#include "UIBase.h"



//定数宣言
const float DMG_SPEED = 0.0025f;      //ダメージバーの速度
const float RCV_SPEED = 0.005f;       //回復バーの速度

class HPGaugeBase : public UIBase
{
public:
	HPGaugeBase(GameObject* parent, std::string fileName);
	~HPGaugeBase();
	void UIUpdate() override;

	void Damage(float value);
	void Recovery(float value);

	void SetGaugePosition(float x, float y)
	{
		transform_.position_.x = x;
		transform_.position_.y = y;
	}
	void SetGaugeScale(XMFLOAT3 scale) { transform_.scale_ = scale; }
	void SetMaxHP(float maxValue) { MAX_HP = maxValue; }

	void SetGaugeInformation();

	float GetStopRatio() { return stopRatio; }
	float GetMoveRatio() { return moveRatio; }

private:

	float MAX_HP;

	float nowHp;	// 現在の体力
	float maxHp;	// 最大体力

	float stopRatio;	// 最大HPに対する固定されたゲージの割合
	float moveRatio;	// 最大HPに対する変化してるゲージの割合

};


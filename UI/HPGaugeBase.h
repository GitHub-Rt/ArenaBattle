#pragma once
#include "../Engine/GameObject.h"

// 使用する画像の種類
enum class FramePict
{
	PICT_FRAME = 0,
	PICT_GREEN,
	PICT_LGREEN,
	PICT_RED,
	PICT_MAX
};

//定数宣言
const float DMG_SPEED = 0.0025f;      //ダメージバーの速度
const float RCV_SPEED = 0.005f;       //回復バーの速度

class HPGaugeBase : public GameObject
{
public:
	HPGaugeBase(GameObject* parent, std::string fileName);
	~HPGaugeBase();
	void Update() override;
	void GaugeImageDraw(int pictHandle, Transform trans);
	void Release() override;

	void Damage(float value);
	void Recovery(float value);

	int GaugeImageLoad(std::string fileName);

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


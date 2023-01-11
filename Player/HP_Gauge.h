#pragma once
#include "../Engine/Image.h"
#include "../Engine/Transform.h"

class HP_Gauge
{
	Sprite* backGround;	//ゲージ枠
	Transform* pixcel;		//位置
	float maxValue;		//最大値
	float damageVal;	//ダメージ量
	float currentVal;	//現在体力量
	float width;		//幅


public:
	HP_Gauge(Sprite* backGroudTex, Transform* pixcelTras, float maxValue, float startValue,float width_);
	void SetDamage(float damage);
	void Load();
	void Draw(Sprite* sp);

};
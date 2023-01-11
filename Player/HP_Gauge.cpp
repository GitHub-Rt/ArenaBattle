#include "HP_Gauge.h"


HP_Gauge::HP_Gauge(Sprite* backGroudTex, Transform* pixcelTras, float maxValue, float startValue,float width_)
{
	backGround = backGroudTex;
	pixcel = pixcelTras;
	maxValue = maxValue;
	currentVal = startValue;
	width = width_;
}

void HP_Gauge::SetDamage(float damage)
{
	damageVal = damage;
}

void HP_Gauge::Load()
{
	Sprite* sp = new Sprite;
	Transform* tf = new Transform;

	//ƒQ[ƒW‚Ì‰Šú‰»
	sp->Load("HP_GaugeFrame.jpg");

	
	float width = 300.0f;

	HP_Gauge(sp, tf, 100, 100, width);
}

void HP_Gauge::Draw(Sprite* sp)
{
	//ƒQ[ƒW—Ê‚ðŒvŽZ
	float checkWidth = (currentVal / maxValue) * width;

	//ƒQ[ƒW‚Ì’†g‚ð•`‰æ
	sp->Draw(pixcelTras,)
}
#include "HP_Gauge.h"


HP_Gauge::HP_Gauge(GameObject* parent)
	:GameObject(parent, "Player")
{

}

HP_Gauge::~HP_Gauge()
{

}


void HP_Gauge::Initialize()
{
	Sprite* sp1 = new Sprite;
	Sprite* sp2 = new Sprite;
	Transform* tf = new Transform;
	tf->position_.x = 0;
	tf->position_.y = 0;
	tf->position_.z = 0;

	//ÉQÅ[ÉWÇÃèâä˙âª
	sp1->Load("HP_GaugeFrame.jpg");
	sp2->Load("HP_Gauge.jpg");

	float width = 300.0f;

	RECT rc = { 0,0,300,400 };

	SetGauge(sp1, sp2, tf, 100, 100, width, rc);
}

void HP_Gauge::Update()
{
	

	if (isDamage)
	{
		width = CalcHP();
		isDamage = false;
	}
}


void HP_Gauge::Draw()
{
	//ÉQÅ[ÉWògÇï`âÊ
	backGround->Draw(*pixcel, rc, 0.0f);

	//ÉQÅ[ÉWÇÃíÜêgÇï`âÊ
	ground->Draw(*pixcel, RECT{ 0,0,(long)width,0 }, 0.0f);

}


void HP_Gauge::Release ()
{

}



void HP_Gauge::SetGauge(Sprite* backGroudTex,Sprite* ground_, Transform* pixcelTras, float maxValue, float startValue,float width_,RECT rc_)
{
	backGround = backGroudTex;
	ground = ground_;
	pixcel = pixcelTras;
	maxValue = maxValue;
	currentVal = startValue;
	width = width_;
	rc = rc_;
}

void HP_Gauge::SetDamage(float damage)
{
	isDamage = true;
	damageVal = damage;
}

float HP_Gauge::CalcHP()
{
	//ÉQÅ[ÉWó ÇåvéZ
	float checkWidth = (currentVal / maxValue) * width;

	return checkWidth;
}
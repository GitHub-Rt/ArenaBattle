#pragma once
#include "../Engine/Image.h"
#include "../Engine/Transform.h"
#include "../Engine/GameObject.h"

class HP_Gauge : public GameObject
{
	Sprite* backGround;	//ゲージ枠
	Sprite* ground;		//ゲージ
	Transform* pixcel;	//位置
	float maxValue;		//最大値
	float damageVal;	//ダメージ量
	float currentVal;	//現在体力量
	float width;		//幅
	RECT rc;			//四角形の幅、高さ、場所
	bool isDamage;		//ダメージフラグ


public:
	void SetGauge(Sprite* backGroudTex, Sprite* ground_, Transform* pixcelTras, float maxValue, float startValue, float width_, RECT rc_);
	void SetDamage(float damage);
	float CalcHP();

	HP_Gauge(GameObject* parent);
	~HP_Gauge();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};
#pragma once
#include "../Engine/GameObject.h"


class HP_Gauge : public GameObject
{
    float HP = 300.0f;     //初期HP(画像横:300)
	float HP_Remaining = HP;	//残りのHP量
	float Damage_amount;	//ダメージ量
    float checkHP;          //描画時のHP管理
	int hPict_[3];    //画像番号( 0 : frame, 1 : HP, 2 : Damage) 
    bool isDamage;      //ダメージを受けたかどうか

public:
    HP_Gauge(GameObject* parent);  
    ~HP_Gauge();    
    void Initialize() override;   
    void Update() override;      
    void Draw() override;
    void Release() override;

    /// <summary>
    /// ダメージ量を格納
    /// </summary>
    /// <param name="damage"></param>
    void SetDamage(int damage);


    /// <summary>
    /// 残り体力を計算
    /// </summary>
    /// <returns>残り体力量(FLOAT)</returns>
    float PercentCalc(float HP_Remaining,float Damage_amount);

    /// <summary>
    /// HPゲージを表示
    /// </summary>
    /// <param name="HP_Remaining"></param>
    void HPDraw(float HP_Remaining);
};


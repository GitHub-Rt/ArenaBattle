#pragma once
#include "../Engine/GameObject.h"

//体力ゲージを管理するクラス
class Gauge : public GameObject
{
public:
    Gauge(GameObject* parent);
    ~Gauge();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    ////////////////////////////////////////

    //ダメージを受ける
    //引数：value  ダメージ量
    void Damage(float value);

    //回復
    //引数：value  回復量
    void Recovery(float value);


    void SetGaugePosition(XMFLOAT3 pos) { transform_.position_ = pos; }
    void SetGaugeScale(XMFLOAT3 scale) { transform_.scale_ = scale; }


private:
    float nowHp_; //現在のＨＰ
    float maxHp_; //最大ＨＰ


    float stopRatio_;       //最大HPに対する固定されたゲージの割合
    float moveRatio_;       //最大HPに対する変化してるゲージの割合



    //使用する画像の種類
    enum class FramePict
    {
        PICT_FRAME = 0,
        PICT_GREEN,
        PICT_LGREEN,
        PICT_RED,
        PICT_MAX
    };

    //画像番号
    int hPict_[5];


};
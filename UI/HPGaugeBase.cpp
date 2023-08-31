#include "HPGaugeBase.h"

HPGaugeBase::HPGaugeBase(GameObject* parent, std::string fileName)
	: UIBase(parent, fileName)
{
    MAX_HP = 0;

    nowHp = 0;
    maxHp = 0;

    stopRatio = 0;
    moveRatio = 0;
}

HPGaugeBase::~HPGaugeBase()
{

}

void HPGaugeBase::UIUpdate()
{
    //ç≈ëÂHPÇ…ëŒÇ∑ÇÈÅAåªç›HPÇÃäÑçá
    stopRatio = (float)nowHp / (float)maxHp;

    //ÉoÅ[ÇìÆÇ©Ç∑
    if (moveRatio < stopRatio) moveRatio += RCV_SPEED;
    if (moveRatio > stopRatio) moveRatio -= DMG_SPEED;
}

void HPGaugeBase::Damage(float value)
{
    nowHp -= value;
    if (nowHp < 0)   nowHp = 0;
}

void HPGaugeBase::Recovery(float value)
{
    nowHp += value;
    if (nowHp > maxHp)   nowHp = maxHp;
}

void HPGaugeBase::SetGaugeInformation()
{
    nowHp = MAX_HP;      //èâä˙HP
    maxHp = MAX_HP;      //MaxHP

    stopRatio = (float)nowHp / (float)maxHp;
    moveRatio = stopRatio;
}
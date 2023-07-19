#include "HPGaugeBase.h"

HPGaugeBase::HPGaugeBase(GameObject* parent, std::string fileName)
	: UIBase(parent, fileName)
{
}

HPGaugeBase::~HPGaugeBase()
{

}

void HPGaugeBase::UIUpdate()
{
    //Å‘åHP‚É‘Î‚·‚éAŒ»İHP‚ÌŠ„‡
    stopRatio = (float)nowHp / (float)maxHp;

    //ƒo[‚ğ“®‚©‚·
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
    nowHp = MAX_HP;      //‰ŠúHP
    maxHp = MAX_HP;      //MaxHP

    stopRatio = (float)nowHp / (float)maxHp;
    moveRatio = stopRatio;
}
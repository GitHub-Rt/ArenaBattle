#include "HPGaugeBase.h"
#include "../Engine/Image.h"




HPGaugeBase::HPGaugeBase(GameObject* parent, std::string fileName)
	: GameObject(parent, fileName)
{
}

HPGaugeBase::~HPGaugeBase()
{

}

void HPGaugeBase::Update()
{
    //Å‘åHP‚É‘Î‚·‚éAŒ»İHP‚ÌŠ„‡
    stopRatio = (float)nowHp / (float)maxHp;

    //ƒo[‚ğ“®‚©‚·
    if (moveRatio < stopRatio) moveRatio += RCV_SPEED;
    if (moveRatio > stopRatio) moveRatio -= DMG_SPEED;
}

void HPGaugeBase::GaugeImageDraw(int pictHandle, Transform trans)
{
    Image::SetTransform(pictHandle, trans);
    Image::Draw(pictHandle);
}

void HPGaugeBase::Release()
{

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

int HPGaugeBase::GaugeImageLoad(std::string fileName)
{
    int hPict = Image::Load("UI/" + fileName);
    assert(hPict >= 0);

    return hPict;
}

void HPGaugeBase::SetGaugeInformation()
{
    nowHp = MAX_HP;      //‰ŠúHP
    maxHp = MAX_HP;      //MaxHP

    stopRatio = (float)nowHp / (float)maxHp;
    moveRatio = stopRatio;
}
#pragma once
#include "StageBase.h"

//•Ç‚ğŠÇ—‚·‚éƒNƒ‰ƒX
class Wall : public StageBase
{
public:
    Wall(GameObject* parent);
    ~Wall();
    void Initialize() override;
};


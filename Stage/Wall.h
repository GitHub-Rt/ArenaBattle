#pragma once
#include "StageBase.h"

//壁を管理するクラス
class Wall : public StageBase
{
public:
    Wall(GameObject* parent);
    ~Wall();
    void Initialize() override;
};


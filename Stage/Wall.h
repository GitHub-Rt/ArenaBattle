#pragma once
#include "StageBase.h"

//�ǂ��Ǘ�����N���X
class Wall : public StageBase
{
public:
    Wall(GameObject* parent);
    ~Wall();
    void Initialize() override;
};


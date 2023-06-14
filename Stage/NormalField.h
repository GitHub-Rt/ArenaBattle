#pragma once
#include "StageBase.h"

//ステージ(床)を管理するクラス
class NormalField : public StageBase
{
public:
    NormalField(GameObject* parent);
    ~NormalField();
    void Initialize() override;
};
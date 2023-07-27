#pragma once
#include "StageBase.h"

//バトルステージを管理するクラス
class Stage : public StageBase
{
public:

    Stage(GameObject* parent);
    ~Stage();
    void Initialize() override; 
    void Draw() override;

};
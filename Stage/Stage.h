#pragma once
#include "StageBase.h"

//�o�g���X�e�[�W���Ǘ�����N���X
class Stage : public StageBase
{
public:

    Stage(GameObject* parent);
    ~Stage();
    void Initialize() override; 
    void Draw() override;

};
#pragma once
#include "StageBase.h"

//�X�e�[�W(��)���Ǘ�����N���X
class NormalField : public StageBase
{
public:
    NormalField(GameObject* parent);
    ~NormalField();
    void Initialize() override;
};
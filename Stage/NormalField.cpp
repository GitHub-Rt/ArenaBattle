#include "NormalField.h"

NormalField::NormalField(GameObject* parent)
    :StageBase(parent, "NormalField")
{
}

NormalField::~NormalField()
{
}

void NormalField::Initialize()
{
    //�����f���̃��[�h
    StageModelLoad("Stage/stage.fbx");
}



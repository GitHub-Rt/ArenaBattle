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
    StageModelLoad("stage.fbx");
}

void NormalField::Draw()
{
    StageDraw(transform_);
}



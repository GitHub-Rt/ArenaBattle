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
    //床モデルのロード
    StageModelLoad("stage.fbx");
}

void NormalField::Draw()
{
    StageDraw(transform_);
}



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
    //è∞ÉÇÉfÉãÇÃÉçÅ[Éh
    StageModelLoad("stage.fbx");
}

void NormalField::Draw()
{
    StageDraw(transform_);
}



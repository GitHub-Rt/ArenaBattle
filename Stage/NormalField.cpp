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
    //°ƒ‚ƒfƒ‹‚Ìƒ[ƒh
    StageModelLoad("Stage/stage.fbx");
}



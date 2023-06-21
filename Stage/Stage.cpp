#include "Stage.h"

Stage::Stage(GameObject* parent)
    :StageBase(parent, "Stage")
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
    //バトルフィールドモデルのロード
    StageModelLoad("Stage/ButtleField.fbx");
}

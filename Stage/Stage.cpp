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
    //�o�g���t�B�[���h���f���̃��[�h
    StageModelLoad("Stage/ButtleField.fbx");
}

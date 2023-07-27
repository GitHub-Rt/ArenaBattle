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
    StageModelLoad("BattleField.fbx");
}

void Stage::Draw()
{
    StageDraw(transform_);
}

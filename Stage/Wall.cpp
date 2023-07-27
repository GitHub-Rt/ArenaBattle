#include "Wall.h"

Wall::Wall(GameObject* parent)
    :StageBase(parent, "Wall")
{
}

Wall::~Wall()
{
}

void Wall::Initialize()
{
    //�ǃ��f���̃��[�h
    StageModelLoad("wall.fbx");
}

void Wall::Draw()
{
    StageDraw(transform_);
}
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
    StageModelLoad("Stage/wall.fbx");
}
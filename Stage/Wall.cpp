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
    //壁モデルのロード
    StageModelLoad("Stage/wall.fbx");
}
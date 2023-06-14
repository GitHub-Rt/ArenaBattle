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
    //•Çƒ‚ƒfƒ‹‚Ìƒ[ƒh
    StageModelLoad("Stage/wall.fbx");
}
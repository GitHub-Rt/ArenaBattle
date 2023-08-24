#include "Building.h"

Building::Building(GameObject* parent)
	: StageBase(parent, "Building")
{

}

Building::~Building()
{

}

void Building::Initialize()
{
	StageModelLoad("building.fbx");

}

void Building::Draw()
{
	StageDraw(transform_);
}
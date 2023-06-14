#include "StageBase.h"
#include "../Engine/Model.h"

StageBase::StageBase(GameObject* parent, std::string fileName)
	:GameObject(parent, fileName)
{
	hModel = -1;
}

StageBase::~StageBase()
{

}

void StageBase::Update()
{

}


void StageBase::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void StageBase::Release()
{
}

void StageBase::StageModelLoad(std::string fileName)
{
	hModel = Model::Load(fileName);
	assert(hModel >= 0);
}
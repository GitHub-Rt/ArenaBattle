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

void StageBase::Release()
{
}

void StageBase::StageModelLoad(std::string fileName)
{
	hModel = Model::Load("Stage/" + fileName);
	assert(hModel >= 0);
}

void StageBase::StageDraw(Transform trans)
{
	Model::SetTransform(hModel, trans);
	Model::Draw(hModel);

}
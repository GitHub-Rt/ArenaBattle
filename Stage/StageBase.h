#pragma once
#include "../Engine/GameObject.h"

class StageBase : public GameObject
{
public:
	StageBase(GameObject* parent, std::string fileName);
	~StageBase();
	void Update() override;
	void Release() override;
	void StageModelLoad(std::string fileName);
	void StageDraw(Transform trans);
	int GetModelHandle() { return hModel; }

private:
	int hModel;
};


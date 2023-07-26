#pragma once
#include "../Engine/GameObject.h"

class SceneManager;

class ControllerOperationScene : public GameObject
{
public:

	ControllerOperationScene(GameObject* parent);
	~ControllerOperationScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	SceneManager* pManager;

};


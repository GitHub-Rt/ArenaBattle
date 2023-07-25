#pragma once
#include "../Engine/GameObject.h"

class SceneManager;
class SelectBox;

class StartScene : public GameObject
{
public:

	StartScene(GameObject* parent);
	~StartScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	SceneManager* pManager;
	SelectBox* pBox;

};


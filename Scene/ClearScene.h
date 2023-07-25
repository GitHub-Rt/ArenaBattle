#pragma once
#include "../Engine/GameObject.h"

class SceneManager;

class ClearScene : public GameObject
{
public:

	ClearScene(GameObject* parent);
	~ClearScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	SceneManager* pManager;

};


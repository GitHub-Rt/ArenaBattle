#pragma once
#include "../Engine/GameObject.h"

class SceneManager;

class OverScene : public GameObject
{
public:

	OverScene(GameObject* parent);
	~OverScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	
	SceneManager* pManager;

};


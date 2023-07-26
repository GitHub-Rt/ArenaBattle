#pragma once
#include "../Engine/GameObject.h"

class SceneManager;

class KeyboardOperationScene : public GameObject
{
public:

	KeyboardOperationScene(GameObject* parent);
	~KeyboardOperationScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	SceneManager* pManager;

};


#pragma once
#include "../Engine/GameObject.h"

class SceneManager;
class SelectBox;

class ReleaseScene : public GameObject
{
public:

	ReleaseScene(GameObject* parent);
	~ReleaseScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	SceneManager* pManager;
	SelectBox* pBox;
};


#pragma once
#include "../Engine/GameObject.h"

class SceneManager;

class Shadow : public GameObject
{
public:

	Shadow(GameObject* parent);
	~Shadow();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void SetShadow();

private:

	int hModel;
	GameObject* parentObj;
	SceneManager* pManager;
};


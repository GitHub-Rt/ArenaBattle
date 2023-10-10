#pragma once
#include "../Engine/GameObject.h"

class SceneManager;
class GameSound;

class HowToPlayScene : public GameObject
{
public:

	HowToPlayScene(GameObject* parent);
	~HowToPlayScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	SceneManager* pManager;
	GameSound* pSound;

};


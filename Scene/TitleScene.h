#pragma once
#include "../Engine/GameObject.h"

class SceneManager;
class GameSound;
class TitleImage;

class TitleScene : public GameObject
{
public:

	TitleScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:

	SceneManager* pManager;
	GameSound* pSound;
	TitleImage* pImage;
};


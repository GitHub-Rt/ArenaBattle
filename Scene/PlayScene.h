#pragma once
#include "../Engine/GameObject.h"

class SceneManager;

class PlayScene : public GameObject
{
public:

	PlayScene(GameObject* parent);
	~PlayScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	// バトル開始するための処理
	void BattleStart();

private:

	SceneManager* pManager;

};


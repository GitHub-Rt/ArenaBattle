#pragma once
#include "../Engine/GameObject.h"

class SceneManager;
class GameSound;
class SelectBox;

// StartSceneの遷移先
enum class StartState
{
	GameStart,
	Controller,
	Keyboard
};

class StartScene : public GameObject
{
public:

	StartScene(GameObject* parent);
	~StartScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	// 状態とUIの表示位置を変更する関数
	void ChangeStateUIPosition();

private:

	SceneManager* pManager;
	GameSound* pSound;
	SelectBox* pBox;
	StartState nowState;
};


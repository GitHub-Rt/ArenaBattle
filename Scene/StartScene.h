#pragma once
#include "../Engine/GameObject.h"

class SceneManager;
class GameSound;
class SelectBox;

// StartScene�̑J�ڐ�
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

	// ��Ԃ�UI�̕\���ʒu��ύX����֐�
	void ChangeStateUIPosition();

private:

	SceneManager* pManager;
	GameSound* pSound;
	SelectBox* pBox;
	StartState nowState;
};


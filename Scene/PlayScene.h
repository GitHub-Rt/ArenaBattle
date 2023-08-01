#pragma once
#include "../Engine/GameObject.h"

class SceneManager;
class GameSound;
class SelectBox;
class Player;

enum class GameLevel
{
	Easy,
	Hard
};

class PlayScene : public GameObject
{
public:

	PlayScene(GameObject* parent);
	~PlayScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	// �o�g���J�n���邽�߂̏���
	void BattleStart();

private:

	SceneManager* pManager;
	GameSound* pSound;
	SelectBox* pBox;
	Player* pPlayer;
	GameLevel nowLevel;
};


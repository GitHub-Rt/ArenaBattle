#pragma once
#include "../Engine/GameObject.h"

class SceneManager;
class GameSound;
class SelectBox;

enum class ReleaseState
{
	BackGame,
	ExitGame
};

class ReleaseScene : public GameObject
{
public:

	ReleaseScene(GameObject* parent);
	~ReleaseScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	// ó‘Ô‚ÆUI‚Ì•\¦ˆÊ’u‚ğ•ÏX‚·‚éŠÖ”
	void ChangeStateUIPosition();

private:

	SceneManager* pManager;
	GameSound* pSound;
	SelectBox* pBox;
	ReleaseState nowState;
};


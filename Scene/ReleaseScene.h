#pragma once
#include "../Engine/GameObject.h"

class SceneManager;
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

	// 状態とUIの表示位置を変更する関数
	void ChangeStateUIPosition();

private:

	SceneManager* pManager;
	SelectBox* pBox;
	ReleaseState nowState;
};


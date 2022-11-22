#include "GameOverScene.h"
#include "Engine/SceneManager.h"


//デバッグ用
#include "Engine/Input.h"

//コンストラクタ
GameOverScene::GameOverScene(GameObject* parent)
	: GameObject(parent, "GameOverScene")
{
}

//初期化
void GameOverScene::Initialize()
{
}

//更新
void GameOverScene::Update()
{
	//スタートボタンが押されたらプレイシーンへ
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START, 0))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void GameOverScene::Draw()
{
}

//開放
void GameOverScene::Release()
{
}
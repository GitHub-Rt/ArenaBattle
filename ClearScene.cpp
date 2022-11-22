#include "ClearScene.h"
#include "Engine/SceneManager.h"


//デバッグ用
#include "Engine/Input.h"

//コンストラクタ
ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene")
{
}

//初期化
void ClearScene::Initialize()
{
}

//更新
void ClearScene::Update()
{
	//スタートボタンが押されたらプレイシーンへ
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START, 0))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void ClearScene::Draw()
{
}

//開放
void ClearScene::Release()
{
}
#include "GameOverScene.h"
#include "SceneManager.h"

#include "../Engine/Image.h"
#include "../Engine/Input.h"

//コンストラクタ
GameOverScene::GameOverScene(GameObject* parent)
	: GameObject(parent, "GameOverScene"), hPict_(-1)
{
}

//初期化
void GameOverScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("GameOver.jpg");
	assert(hPict_ >= 0);
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
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void GameOverScene::Release()
{
}
#include "ClearScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"

#include "Engine/Input.h"

//コンストラクタ
ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene"), hPict_(-1)
{
}

//初期化
void ClearScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("GameClear.jpg");
	assert(hPict_ >= 0);
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
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void ClearScene::Release()
{
}
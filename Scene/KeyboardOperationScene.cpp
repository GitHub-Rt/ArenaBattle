#include "KeyboardOperationScene.h"
#include "SceneManager.h"

#include "../Engine/Input.h"

#include "../UI/BackGroundImage.h"
#include "../UI/KeyboardOperationImage.h"

KeyboardOperationScene::KeyboardOperationScene(GameObject* parent)
	: GameObject(parent, "KeyboardOperationScne")
{
	pManager = nullptr;
}

KeyboardOperationScene::~KeyboardOperationScene()
{

}

void KeyboardOperationScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");

	Instantiate<BackGroundImage>(this);
	Instantiate<KeyboardOperationImage>(this);
}

void KeyboardOperationScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) || Input::IsKeyDown(DIK_ESCAPE))
	{
		pManager->ChangeScene(SCENE_ID::SCENE_ID_TITLE);
	}
}

void KeyboardOperationScene::Draw()
{

}

void KeyboardOperationScene::Release()
{

}
#include "ControllerOperationScene.h"
#include "SceneManager.h"

#include "../Engine/Input.h"

#include "../UI/BackGroundImage.h"
#include "../UI/ControllerOperationImage.h"

ControllerOperationScene::ControllerOperationScene(GameObject* parent)
	: GameObject(parent, "ControllerOperationScene")
{
	pManager = nullptr;
}

ControllerOperationScene::~ControllerOperationScene()
{

}

void ControllerOperationScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");

	Instantiate<BackGroundImage>(this);
	Instantiate<ControllerOperationImage>(this);
}

void ControllerOperationScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) || Input::IsKeyDown(DIK_ESCAPE))
	{
		pManager->ChangeScene(SCENE_ID::SCENE_ID_TITLE);
	}
}

void ControllerOperationScene::Draw()
{

}

void ControllerOperationScene::Release()
{

}
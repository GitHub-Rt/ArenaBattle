#include "StartScene.h"

#include "SceneManager.h"
#include "../UI/BackGroundImage.h"
#include "../UI/StartImage.h"
#include "../UI/SelectBox.h"

#include "../Engine/Input.h"

StartScene::StartScene(GameObject* parent)
	: GameObject(parent, "StartScene")
{
	pManager = nullptr;
	pBox = nullptr;
}

StartScene::~StartScene()
{

}

void StartScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");

	Instantiate<BackGroundImage>(this);
	Instantiate<StartImage>(this);
	pBox = Instantiate<SelectBox>(this);
}

void StartScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) || Input::IsKeyDown(DIK_ESCAPE))
	{
		pManager->ChangeScene(SCENE_ID::SCENE_ID_TITLE);
	}

	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
	{
		
	}
}

void StartScene::Draw()
{

}

void StartScene::Release()
{

}
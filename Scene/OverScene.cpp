#include "OverScene.h"
#include "SceneManager.h"

#include "../Engine/Input.h"

#include "../UI/BackGroundImage.h"
#include "../UI/OverImage.h"

OverScene::OverScene(GameObject* parent)
	: GameObject(parent, "OverScene")
{
	pManager = nullptr;
}

OverScene::~OverScene()
{

}

void OverScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");

	Instantiate<BackGroundImage>(this);
	Instantiate<OverImage>(this);
}

void OverScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
	{
		pManager->ChangeScene(SCENE_ID::SCENE_ID_TITLE);
	}
}

void OverScene::Draw()
{

}

void OverScene::Release()
{

}
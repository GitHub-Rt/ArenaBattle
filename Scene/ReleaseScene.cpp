#include "ReleaseScene.h"

#include "SceneManager.h"
#include "../UI/BackGroundImage.h"
#include "../UI/ReleaseImage.h"
#include "../UI/SelectBox.h"

#include "../Engine/Input.h"

ReleaseScene::ReleaseScene(GameObject* parent)
	: GameObject(parent, "ReleaseScene")
{
	pManager = nullptr;
	pBox = nullptr;
}

ReleaseScene::~ReleaseScene()
{

}

void ReleaseScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");

	Instantiate<BackGroundImage>(this);
	Instantiate<ReleaseImage>(this);
	pBox = Instantiate<SelectBox>(this);
}

void ReleaseScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START) || Input::IsKeyDown(DIK_ESCAPE))
	{
		PostQuitMessage(0);	//ÉvÉçÉOÉâÉÄèIóπ
	}
}

void ReleaseScene::Draw()
{

}

void ReleaseScene::Release()
{

}
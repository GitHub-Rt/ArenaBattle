#include "DebugScene.h"
#include "../Stage/Stage.h"

#include "../imgui/imguiObject.h"


#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"

#include "../Engine/Input.h"
#include "SceneManager.h"

DebugScene::DebugScene(GameObject* parent)
	: GameObject(parent, "DebugScene")
{

}

void DebugScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<Robot>(this);

	Instantiate<Enemy>(this);

	Instantiate<imguiObject>(this);
}

void DebugScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START))
	{
		PostQuitMessage(0);	//プログラム終了
	}
}

void DebugScene::Draw()
{

}

void DebugScene::Release()
{

}


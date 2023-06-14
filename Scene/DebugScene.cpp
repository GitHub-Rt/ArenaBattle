#include "DebugScene.h"
#include "../Stage/NormalField.h"

#include "../imgui/imguiObject.h"


#include "../Character/Player.h"
#include "../Character/Robot.h"

#include "../Engine/Input.h"
#include "SceneManager.h"

DebugScene::DebugScene(GameObject* parent)
	: GameObject(parent, "DebugScene")
{

}

void DebugScene::Initialize()
{
	Instantiate<NormalField>(this);
	Instantiate<Player>(this);
	Instantiate<Robot>(this);

	Instantiate<imguiObject>(this);
}

void DebugScene::Update()
{
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_START))
	{
		PostQuitMessage(0);	//ƒvƒƒOƒ‰ƒ€I—¹
	}
}

void DebugScene::Draw()
{

}

void DebugScene::Release()
{

}


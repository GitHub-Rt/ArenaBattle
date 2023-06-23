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
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		pEnemy[i] = nullptr;
	}
}

void DebugScene::Initialize()
{


	Instantiate<Stage>(this);

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		pEnemy[i] = Instantiate<Enemy>(this);
	}

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


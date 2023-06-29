#include "DebugScene.h"
#include "../Stage/Stage.h"

#include "../imgui/imguiObject.h"


#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"
#include "../Manager/EnemyManager.h"

#include "../Engine/Input.h"
#include "SceneManager.h"

const int EnemyTimer = 30;

DebugScene::DebugScene(GameObject* parent)
	: GameObject(parent, "DebugScene")
{
	pBoss = nullptr;

}

void DebugScene::Initialize()
{
	

	Instantiate<Stage>(this);

	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
	}
	//pBoss = Instantiate<EnemyBoss>(this);
	
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

	/*if (EnemyManager::IsListEmpty())
	{
		timer++;
		if (timer > EnemyTimer)
		{
			timer = 0;
			

			for (int i = 0; i < ENEMY_COUNT; i++)
			{
				EnemyManager::AddEnemyList(Instantiate<Enemy>(this));
			}

		}		
	}*/
	
	/*if (pBoss->IsVisibled() == false && enemyCount > MAX_ENEMY_COUNT)
	{
		pBoss->BossEntry();
	}*/
}

void DebugScene::Draw()
{

}

void DebugScene::Release()
{

}

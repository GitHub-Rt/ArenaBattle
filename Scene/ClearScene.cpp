#include "ClearScene.h"
#include "SceneManager.h"

#include "../Engine/Input.h"

#include "../UI/BackGroundImage.h"
#include "../UI/ClearImage.h"

ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene")
{
	pManager = nullptr;
}

ClearScene::~ClearScene()
{

}

void ClearScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");

	Instantiate<BackGroundImage>(this);
	Instantiate<ClearImage>(this);
}

void ClearScene::Update()
{

}

void ClearScene::Draw()
{

}

void ClearScene::Release()
{

}

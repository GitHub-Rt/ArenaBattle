#include "KeyboardOperationScene.h"
#include "SceneManager.h"



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
}

void KeyboardOperationScene::Update()
{

}

void KeyboardOperationScene::Draw()
{

}

void KeyboardOperationScene::Release()
{

}
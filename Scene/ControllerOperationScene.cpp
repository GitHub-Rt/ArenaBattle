#include "ControllerOperationScene.h"
#include "SceneManager.h"

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
}

void ControllerOperationScene::Update()
{

}

void ControllerOperationScene::Draw()
{

}

void ControllerOperationScene::Release()
{

}
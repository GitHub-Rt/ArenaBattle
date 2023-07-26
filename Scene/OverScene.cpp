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

}

void OverScene::Draw()
{

}

void OverScene::Release()
{

}
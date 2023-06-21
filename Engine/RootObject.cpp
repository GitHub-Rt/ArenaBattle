#include "RootObject.h"
#include "../Scene/SceneManager.h"

#include "../Character/Player.h"

RootObject::RootObject():
	GameObject(nullptr, "RootObject")
{
}


RootObject::~RootObject()
{
}

void RootObject::Initialize()
{
	Instantiate<SceneManager>(this);
}

void RootObject::Update()
{
}

void RootObject::Draw()
{
}

void RootObject::Release()
{
}

void RootObject::PlayerCamera()
{
	Player* pPlayer = (Player*)FindObject("Player");
	pPlayer->NormalCamera();
}
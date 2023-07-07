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

XMFLOAT3 RootObject::PlayerCameraPos()
{
	Player* pPlayer = (Player*)FindObject("Player");
	return pPlayer->GetCameraPosition();
}

XMFLOAT3 RootObject::PlayerCameraFocas()
{
	Player* pPlayer = (Player*)FindObject("Player");
	return pPlayer->GetCameraFocas();
}
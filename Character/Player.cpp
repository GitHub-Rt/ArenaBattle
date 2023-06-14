#include "Player.h"
#include "../Engine/Input.h"

// 定数宣言




void Player::SetData()
{
}


Player::Player(GameObject* parent)
	:CharacterBase(parent, "Player")
{
}

Player::~Player()
{

}

void Player::Initialize()
{
	CharacterModelLoad("Character/Model/player.fbx");
}

void Player::Release()
{
}

void Player::CharacterUpdate()
{

}

void Player::CharacterMove()
{

}

void Player::CharacterAttack()
{

}


void Player::CharacterCheckHP()
{
}

void Player::CharacterTakeDamage(float damage)
{
}




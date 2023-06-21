#include "EnemyBase.h"

EnemyBase::EnemyBase(GameObject* parent, std::string fileName)
	: CharacterBase(parent, fileName)
{

}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Release()
{
	EnemyRelease();
}

void EnemyBase::CharacterJumpAction()
{

}

void EnemyBase::CharacterDodingAction()
{

}
#include "EnemyBoss.h"
#include "../UI/EnemyBossGauge.h"

EnemyBoss::EnemyBoss(GameObject* parent)
	: EnemyBase(parent, "EnemyBoss")
{
	pGauge = nullptr;
}

EnemyBoss::~EnemyBoss()
{

}

void EnemyBoss::SetData()
{

}

void EnemyBoss::Initialize()
{
	pGauge = Instantiate<EnemyBossGauge>(GetParent());

	CharacterModelLoad("enemyBoss.fbx");
}

void EnemyBoss::EnemyRelease()
{

}

void EnemyBoss::EnemyUpdate()
{

}

void EnemyBoss::CharacterIdleAction()
{

}

void EnemyBoss::CharacterMove()
{

}

void EnemyBoss::CharacterAttack()
{

}

void EnemyBoss::CharacterTakeDamage(float damage)
{

}

void EnemyBoss::CharacterCheckHP()
{

}

void EnemyBoss::DrawEffect()
{

}

void EnemyBoss::CharacterStunAction()
{

}

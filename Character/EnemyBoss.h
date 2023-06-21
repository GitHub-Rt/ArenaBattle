#pragma once
#include "EnemyBase.h"
class EnemyBoss : public EnemyBase
{
	EnemyBoss(GameObject* parent);
	~EnemyBoss();

	void SetData() override;
	void Initialize() override;
	void EnemyRelease() override;
	void CharacterUpdate() override;
	void CharacterIdleAction() override;
	void CharacterMove() override;
	void CharacterAttack() override;
	void CharacterTakeDamage(float damage) override;
	void CharacterCheckHP() override;



	void DrawEffect() override;
	void CharacterStunAction() override;
};


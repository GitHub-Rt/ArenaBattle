#pragma once
#include "EnemyBase.h"

class EnemyBossGauge;

class EnemyBoss : public EnemyBase
{
public:
	EnemyBoss(GameObject* parent);
	~EnemyBoss();

	void SetData() override;
	void Initialize() override;
	void EnemyRelease() override;
	void EnemyUpdate() override;
	void CharacterIdleAction() override;
	void CharacterMove() override;
	void CharacterAttack() override;
	void CharacterTakeDamage(float damage) override;
	void CharacterCheckHP() override;



	void DrawEffect() override;
	void CharacterStunAction() override;

private:
	EnemyBossGauge* pGauge;
};


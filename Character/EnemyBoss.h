#pragma once
#include "EnemyBase.h"

class EnemyBossGauge;

enum class EnemyBossData
{
	EntryFirstPosY = 1,
	AttackIntervalTime,
};


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
	void OnCollision(GameObject* pTarget) override;

	// EnemyBoss“oêˆ—(“oê‚ªI‚í‚Á‚½‚çtrue‚ğ•Ô‚·)
	void BossEntry();

	// Update“™‚Ìˆ—‚ğŠJn‚·‚éŠÖ”
	void ProcessStart();

private:
	
	// InternalData‚©‚çæ“¾‚·‚é’è”
	float ENTRY_FIRST_POS_Y;		// ‰ŠúyÀ•W
	int ATTACK_INTERVAL_TIME;		// UŒ‚ŠÔŠuŠÔ

	// ‚»‚Ì‘¼‚Ì’è”
	float ENTRY_POS_Y;				// ’…’n‚ÌyÀ•W
	
	EnemyBossGauge* pGauge;

	float hp;
};


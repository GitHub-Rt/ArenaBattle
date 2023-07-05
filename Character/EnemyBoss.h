#pragma once
#include "EnemyBase.h"

class Player;
class EnemyBossGauge;

enum class EnemyBossData
{
	EntryFirstPosY = 1,
	AttackIntervalTime,
	DamageTime,
	RateForMaxStrength,
	TotalDamagesUpAILevel,
};

enum class BossAttackState
{
	NoAttack = (unsigned int)(1 << 0),
	BulletAttack = (unsigned int)(1 << 1),
	SpiralMoveAttack = (unsigned int)(1 << 2),
	WavesAttack = (unsigned int)(1 << 3),
	JumpAttack = (unsigned int)(1 << 4),
	SpecialAttack = (unsigned int)(1 << 5),
	MaxAttackState
};

enum class BossAttackModelHandle
{
	Bullet,
	Wave,
};

enum class BossAIState
{
	Allowance = 1,	// –û’f(—]—T)ó‘Ô
	Normal,			// ’Êíó‘Ô
	Caution			// Œx‰ú(—Õí)ó‘Ô
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
	void OnCollision(GameObject* pTarget, Collider* nowCollider) override;

	// UŒ‚Ží—Þ‚Ì‘I‘ð
	void AttackTypeSelection();

	// UŒ‚ó‘ÔŽü‚è‚ÌŠÖ”
	// UŒ‚ó‘Ô‚ð—§‚Ä‚é
	void ChangeAttackState(BossAttackState nextState);

	// UŒ‚ó‘Ô‚ð•š‚¹‚é
	void ClearAttackState(BossAttackState state);
	
	// ‚Ç‚ÌUŒ‚ó‘Ô‚à—§‚Á‚Ä‚¢‚È‚©‚Á‚½‚çNoAttack‚É•ÏX‚·‚é
	void ChangeForNoAttack();

	// UŒ‚ó‘Ô‚ÌŽæ“¾(ó‘Ô‚ª—§‚Á‚Ä‚¢‚½‚çtrue)
	bool IsAttackState(BossAttackState state) { return (bossAttackState & (unsigned int)state) != 0; }

	// UŒ‚ƒ‚ƒfƒ‹‚ÆƒvƒŒƒCƒ„[‚Ìƒ_ƒ[ƒWˆ—
	void AttackModelDamageToPlayer(BossAttackModelHandle attackSource);

	// ŠeUŒ‚‚ÌŠÖ”
	void BulletAttackAction();
	void SpiralMoveAttackAction();
	void WavesAttackAction();
	void JumpAttackAction();
	void SpecialAttackAction();

	// ŠeUŒ‚•Ï”‚ÌƒŠƒZƒbƒg
	void AttackVariableReset(BossAttackState nowState);

	void Damage(float damage);
	void DamageMotion();

	// EnemyBoss“oêˆ—(“oê‚ªI‚í‚Á‚½‚çtrue‚ð•Ô‚·)
	bool BossEntry();

	// Update“™‚Ìˆ—‚ðŠJŽn‚·‚éŠÖ”
	void ProcessStart();

#ifdef  _DEBUG

	float GetHP() { return hp; }

#endif


private:
	
	// InternalData‚©‚çŽæ“¾‚·‚é’è”
	float ENTRY_FIRST_POS_Y;		// ‰ŠúyÀ•W
	int ATTACK_INTERVAL_TIME;		// UŒ‚ŠÔŠuŽžŠÔ
	int DAMAGE_TIME;				// ”íƒ_ƒ[ƒWŽžŠÔ
	int RATE_FOR_MAX_STRENGTH;		// “ÁŽêUŒ‚‚ðs‚¤Û‚ÌÅ‘å‘Ì—Í‚É‘Î‚·‚éŠ„‡
	int TOTAL_DAMAGES_UP_AI_LEVEl;	// AIƒŒƒxƒ‹‚ðã‚°‚é‡Œvƒ_ƒ[ƒW—Ê

	// ‚»‚Ì‘¼‚Ì’è”
	float ENTRY_POS_Y;				// ’…’nŽž‚ÌyÀ•W
	
	// ‘S‘Ì•Ï”
	Player* pPlayer;
	unsigned int bossAttackState;
	BossAIState bossAIState;

	// UŒ‚‘S‘ÌŽü‚è‚Ì•Ï”
	int attackIntervalTimer;
	
	// ’eUŒ‚Žü‚è‚Ì•Ï”

	// ‰QŠªˆÚ“®UŒ‚Žü‚è‚Ì•Ï”

	// ”góUŒ‚‚Ì•Ï”

	// ƒWƒƒƒ“ƒvUŒ‚Žü‚è‚Ì•Ï”

	// “ÁŽêUŒ‚Žü‚è‚Ì•Ï”
	bool isSpecialAttack;	// “ÁŽêUŒ‚‚ðs‚Á‚½‚©‚Ç‚¤‚©


	// ‘Ì—ÍŽü‚è‚Ì•Ï”
	EnemyBossGauge* pGauge;
	float hp;

	// “oê‰‰oŽü‚è‚Ì•Ï”
	bool isWarningStart;

	// ”íƒ_ƒ[ƒWŽü‚è‚Ì•Ï”
	int damageTimer;
	float totalDamages;
};


#pragma once
#include "EnemyBase.h"

class Player;
class EnemyBossGauge;

enum class EnemyBossData
{
	EntryFirstPosY = 1,
	AttackIntervalTime,
	DamageTime,
};

enum class BossAttackState
{
	NoAttack,
	BulletAttack,
	SpiralMoveAttack,
	WavesAttack,
	JumpAttack,
	SpecialAttack
};

class EnemyBoss : public EnemyBase
{
public:

	BossAttackState GetAttackState() { return bossAttackState; }

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


	void DamageMotion();

	// EnemyBoss登場処理(登場が終わったらtrueを返す)
	void BossEntry();

	// Update等の処理を開始する関数
	void ProcessStart();

#ifdef  _DEBUG

	float GetHP() { return hp; }

#endif


private:
	
	// InternalDataから取得する定数
	float ENTRY_FIRST_POS_Y;		// 初期y座標
	int ATTACK_INTERVAL_TIME;		// 攻撃間隔時間
	int DAMAGE_TIME;				// 被ダメージ時間

	// その他の定数
	float ENTRY_POS_Y;				// 着地時のy座標
	
	Player* pPlayer;
	EnemyBossGauge* pGauge;


	BossAttackState bossAttackState;

	float hp;

	// 被ダメージ周り変数
	int damageTimer;
};


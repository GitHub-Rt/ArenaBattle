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

	// EnemyBoss登場処理(登場が終わったらtrueを返す)
	void BossEntry();

	// Update等の処理を開始する関数
	void ProcessStart();

private:
	
	// InternalDataから取得する定数
	float ENTRY_FIRST_POS_Y;		// 初期y座標
	int ATTACK_INTERVAL_TIME;		// 攻撃間隔時間

	// その他の定数
	float ENTRY_POS_Y;				// 着地時のy座標
	
	EnemyBossGauge* pGauge;

	float hp;
};


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

	// EnemyBoss�o�ꏈ��(�o�ꂪ�I�������true��Ԃ�)
	void BossEntry();

	// Update���̏������J�n����֐�
	void ProcessStart();

private:
	
	// InternalData����擾����萔
	float ENTRY_FIRST_POS_Y;		// ����y���W
	int ATTACK_INTERVAL_TIME;		// �U���Ԋu����

	// ���̑��̒萔
	float ENTRY_POS_Y;				// ���n����y���W
	
	EnemyBossGauge* pGauge;

	float hp;
};


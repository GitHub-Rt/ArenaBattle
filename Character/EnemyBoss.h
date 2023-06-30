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

	// EnemyBoss�o�ꏈ��(�o�ꂪ�I�������true��Ԃ�)
	void BossEntry();

	// Update���̏������J�n����֐�
	void ProcessStart();

#ifdef  _DEBUG

	float GetHP() { return hp; }

#endif


private:
	
	// InternalData����擾����萔
	float ENTRY_FIRST_POS_Y;		// ����y���W
	int ATTACK_INTERVAL_TIME;		// �U���Ԋu����
	int DAMAGE_TIME;				// ��_���[�W����

	// ���̑��̒萔
	float ENTRY_POS_Y;				// ���n����y���W
	
	Player* pPlayer;
	EnemyBossGauge* pGauge;


	BossAttackState bossAttackState;

	float hp;

	// ��_���[�W����ϐ�
	int damageTimer;
};


#pragma once
#include "EnemyBase.h"

class Player;
class EnemyBossGauge;
class EnemyBossBullet;
class EnemyBossJumpArea;
class EnemyBossSpecialArea;

enum class EnemyBossData
{
	EntryFirstPosY = 1,
	AttackIntervalTime,
	DamageTime,
	RateForMaxStrength,
	TotalDamagesUpAILevel,
	BulletAtkIntervalTime,
	BulletAtkMaxCount,
	BulletAtkMagnification,
	WavesAtkMaxCount,
	WavesAtkMagnification,
	JumpAtkMaxCount,
	JumpAtkBetTimer,
	JumpAtkMagnification,
	TimeUpToSpecialAttack,
	SpecialAtkMagnification,
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
	Allowance = 1,	// ���f(�]�T)���
	Normal,			// �ʏ���
	Caution			// �x��(�Ր�)���
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
	void CharacterMove() override {};
	void CharacterAttack() override;
	void CharacterTakeDamage(float damage) override;
	void CharacterCheckHP() override;
	void DrawEffect() override;
	void CharacterStunAction() override;
	void OnCollision(GameObject* pTarget, Collider* nowCollider) override;

	// �U����ނ̑I��
	void AttackTypeSelection();

	// �U����Ԏ���̊֐�
	// �U����Ԃ𗧂Ă�
	void ChangeAttackState(BossAttackState nextState);

	// �U����Ԃ𕚂���
	void ClearAttackState(BossAttackState state);
	
	// �ǂ̍U����Ԃ������Ă��Ȃ�������NoAttack�ɕύX����
	void ChangeForNoAttack();

	// �U����Ԃ̎擾(��Ԃ������Ă�����true)
	bool IsAttackState(BossAttackState state) { return (bossAttackState & (unsigned int)state) != 0; }

	// �U�����f���ƃv���C���[�̃_���[�W����
	void AttackModelDamageToPlayer(BossAttackModelHandle attackSource, XMVECTOR vec);

	// �U���J�n�܂ł̎��Ԃ��v�����čU�����J�n������֐�
	void AttackStartTimer();


	// �e�U���̊֐�

	void BulletAttackAction();
	void BulletAttackCal(std::string dirName);	// �e�U���ɕK�v�Ȍv�Z���s���X�^�[�g������֐�
	void SpiralMoveAttackAction();
	void WavesAttackAction();
	void JumpAttackAction();
	void SpecialAttackAction();

	// �e�U���ϐ��̃��Z�b�g
	void AttackVariableReset(BossAttackState nowState);

	void Damage(float damage);
	void DamageMotion();

	// EnemyBoss�o�ꏈ��(�o�ꂪ�I�������true��Ԃ�)
	bool BossEntry();

	// Update���̏������J�n����֐�
	void ProcessStart();


	// �����ʒu���ӂɖ߂��Ă������ǂ���(�߂��Ă�����true)
	bool IsFirstPosAround(XMFLOAT3 pos);

#ifdef  _DEBUG

	float GetHP() { return hp; }

#endif


private:
	
	// InternalData����擾����萔
	float ENTRY_FIRST_POS_Y;		// ����y���W
	int ATTACK_INTERVAL_TIME;		// �U���Ԋu����
	int DAMAGE_TIME;				// ��_���[�W����
	int RATE_FOR_MAX_STRENGTH;		// ����U�����s���ۂ̍ő�̗͂ɑ΂��銄��
	int TOTAL_DAMAGES_UP_AI_LEVEl;	// AI���x�����グ�鍇�v�_���[�W��
	int BULLET_ATK_INTERVAL_TIME;	// �e�U���̊Ԋu����
	int BULLET_ATK_MAX_COUNT;		// �e�U���̍ő��
	float BULLET_ATK_MAGNIFICATION;	// �e�U���̔{��
	int WAVES_ATK_MAX_COUNT;		// �g��U���̍ő��
	float WAVES_ATK_MAGNIFICATION;	// �g��U���̔{��
	int JUMP_ATK_MAX_COUNT;			// �W�����v�U���̍ő��
	int JUMP_ATK_BET_TIMER;			// �W�����v�U���̊Ԋu����
	float JUMP_ATK_MAGNIFICATION;	// �W�����v�U���̍U���{��
	int TIME_UP_TO_SPECIAL_ATTACK;	// ����U�����s�܂ł̎���
	float SPECIAL_ATK_MAGNIFICATION;// ����U���̔{��

	// ���̑��̒萔
	float ENTRY_POS_Y;				// ���n����y���W
	
	
	// �S�̕ϐ�
	Player* pPlayer;
	unsigned int bossAttackState;
	BossAIState bossAIState;
	XMFLOAT3 firstPos;

	// �U���S�̎���̕ϐ�
	int attackIntervalTimer;	// �U���Ԋu
	float jumpSpeed;			// �W�����v�̏㏸��
	
	// �e�U������̕ϐ�
	int bulletTimer;	// �U���Ԋu
	int bulletCount;	// �U����


	// �Q���ړ��U������̕ϐ�
	float spiralAngle;		// ��]�p�x
	float spiralRadius;		// ���a
	bool isEndLine;			// �[�ɓ��B�������ǂ���


	// �g��U���̕ϐ�
	int wavesCount;			// �U����
	int wavesJumpTimer;		// �㏸����


	// �W�����v�U������̕ϐ�
	int jumpBetTimer;			// �W�����v�U���̊Ԋu
	int jumpCount;				// �W�����v�U���̍U����
	XMFLOAT3 landingPosition;	// ���n�n�_(�v���C���[�̃|�W�V����)
	EnemyBossJumpArea* pArea;
	bool isPointGetting;		// ���n�n�_�̏����擾�������ǂ���


	// ����U������̕ϐ�
	int specialTimer;					// ����U���J�n�܂ł̎���
	bool isSpecialAttack;				// ����U�����s�������ǂ���
	EnemyBossSpecialArea* pSpecialArea;

	// �̗͎���̕ϐ�
	EnemyBossGauge* pGauge;
	float maxHp;
	float hp;

	// �o�ꉉ�o����̕ϐ�
	bool isWarningStart;

	// ��_���[�W����̕ϐ�
	int damageTimer;
	float totalDamages;
};


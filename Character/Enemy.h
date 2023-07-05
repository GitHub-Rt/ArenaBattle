#pragma once
#include "EnemyBase.h"

enum class AttackState;

enum class EnemyData
{
	AttackStartRange = 1,
	AttackTime = 2,
	DamageTimer = 3
};

class Enemy : public EnemyBase
{
public:
	Enemy(GameObject* parent);
	~Enemy();

	void SetData() override;
	void Initialize() override;
	void Draw() override;
	void EnemyRelease() override;
	void EnemyUpdate() override;
	void CharacterIdleAction() override;
	void CharacterMove() override;
	void CharacterAttack() override;
	void CharacterTakeDamage(float damage) override;
	void CharacterCheckHP() override;
	void OnCollision(GameObject* pTarget, Collider* nowCollider) override;


	void ModelRotate(XMVECTOR vMove);

	// ���W�����v����֐�
	void SmallJump();

	// ��_���[�W���[�V����
	void DamageMotion();

	// �v���C���[�ɐG��Ă��邩�ǂ���
	bool IsPlayerHitting() { return isHittingPlayer; }

	void DrawEffect() override {};
	void CharacterStunAction() override {};

#ifdef _DEBUG

	bool isDamage;

	bool IsDamage() { return isDamage; }

	float GetHP() { return hp; }

#endif


private:

	// InternalDataCSV����l���i�[����ϐ�
	float ATTACK_START_RANGE;		// �U���J�n����͈͂̒���
	int ATTACK_TIME;				// �U������
	int DAMAGE_TIME;				// �_���[�W����
	
	// �S�̕ϐ�
	float hp;	// �̗�
	int hModel;	// ���f���ԍ�

	// �ړ�����̕ϐ�
	XMVECTOR vPrevPos;				// �O��̈ʒu�x�N�g��

	// �U������̕ϐ�
	XMVECTOR vAttackMove;			// �U�����̈ړ��x�N�g��
	int attackTimer;				// �U���^�C�}�[

	// �U���O�W�����v����̕ϐ�
	float beforeJumpY;				// �W�����v�O��y���W
	float jumpSpeed;				// �����x
	bool isJumpSummit;				// �W�����v�̒���ɓ��B�������ǂ���
	bool isStartingAttackMoving;	// �W�����v�������I���Ĉړ����n�߂����ǂ���

	// ��_���[�W����̕ϐ�
	int damageTimer;				// �_���[�W����

	// ���̑�
	bool isHittingPlayer;			// �v���C���[�ɐG��Ă��邩�ǂ���
};


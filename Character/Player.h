#pragma once
#include "CharacterBase.h"

class PolyLine;
class PlayerEffect;

// �U���̏�Ԃ��Ǘ�
enum class AttackState
{
	NoAttack,
	NormalAttack,
	HardAttack
};

// �����f�[�^���i�[���Ă���CSV�t�@�C���̊Y�����ڂɑΉ������s�����Ǘ�����
enum class PlayerData
{
	StrengthRateIncreasingAttack = 1,
	AttackPowerIncreaseRate = 2,
	NormalAttackIncreaseRate = 3,
	HardAttackIncreaseRate = 4,
	NormalAttackTime = 5,
	HardAttackTime = 6,
	DodgeTime = 7,
	RecoveryPotionNumber = 8,
	RecoveryQuantity = 9,
	MaxInvincibleTime = 10
};

class Player : public CharacterBase
{
public:

	// �J�����̕����x�N�g����Ԃ�
	XMFLOAT3 GetCameraDirection() { return cameraDirection; }

	// �U����Ԃ�Ԃ�
	AttackState GetAttackState() { return attackState; }

	void SetData() override;
	Player(GameObject* parent);
	~Player();
	void Initialize()  override;
	void Release() override;
	void CharacterUpdate() override;
	void CharacterIdleAction() override;
	void CharacterMove() override;
	void CharacterAttack() override;
	void CharacterJumpAction() override;
	void CharacterDodingAction() override;
	void CharacterStunAction() override;
	void CharacterTakeDamage(float damage) override;
	void CharacterCheckHP() override;
	void DrawEffect() override;
	void OnCollision(GameObject* pTarget) override;

	// �J��������
	void NormalCamera();	// �ʏ펞�J�����֐�
	
	// �U������
	void NormalAttackAction();	// �ʏ�U���A�N�V����
	void HardAttackAction();	// ���U���A�N�V����

	// ��_���[�W���[�V����
	void DamageTakenMotion();

	// �e���͂��s��ꂽ���ǂ���
	bool IsMoveEntry();			// ��������̓���
	bool IsDodEntry();			// �������̓���
	bool IsAttackEntry();		// �U������̓���
	bool IsRecoverEntry();		// �񕜎���̓���
	bool IsJumpEntry();			// �W�����v����̓���

#ifdef _DEBUG

	XMFLOAT3 camPos;
	XMFLOAT3 camTarget;

	void SetCamera(XMFLOAT3 pos, XMFLOAT3 tar)
	{
		camPos = pos;
		camTarget = tar;
	}

	XMFLOAT3 GetCameraPosition() { return camPos; }
	XMFLOAT3 GetCameraTarget() { return camTarget; }

#endif

private:

	// InternalDataCSV����l���i�[����ϐ�
	float STRENGTH_RATE_INCREASING_ATTACK;	// �U���͂���������̗͂̊������C��
	float ATTACK_POWER_INCREASE_RATE;		// �̗͂̊������C�����̗͂����ɂȂ����Ƃ��̍U���͂̑�����
	float NORMAL_ATTACK_INCREASE_RATE;		// �ʏ�U���̍U���{��
	float HARD_ATTACK_INCREASE_RATE;		// ���U���̍U���{��
	float NORMAL_ATTACK_TIME;				// �ʏ�U���̍U������
	float HARD_ATTACK_TIME;					// ���U���̍U������
	float DODGE_TIME;						// �������
	float RECOVERY_POTION_NUMBER;			// �񕜃|�[�V�����̍ő吔
	float RECOVERY_QUANTITY;				// �񕜗�
	int MAX_INVINCIBLE_TIME;				// �ő喳�G����
	

	// ���͎���̕ϐ�
	bool isTrrigerReset;

	// �ړ�����̕ϐ�
	XMFLOAT3 movingDistance;	// �ړ���
	XMVECTOR vPrevPos;			// �O��̈ʒu�x�N�g��

	// �W�����v����̕ϐ�
	float beforeJumpY;			// �W�����v����O��y���W
	float jumpSpeed;			// �W�����v���x
	bool isJumpSummit;			// �W�����v�̒���ɓ��B�������ǂ���


	// �U������̕ϐ�
	AttackState attackState;		// �U�����
	PlayerEffect* pEffect;			// �G�t�F�N�g�̃|�C���^
	int attackTimer;				// �U������
	XMVECTOR attackVector;			// ���̓x�N�g��

	// �������̕ϐ�
	PolyLine* pLine;			// �|�����C���̃|�C���^
	int dodgeTimer;				// �������

	// �J��������̕ϐ�
	float angleX;				// ���������̃J������]�p�x
	float angleY;				// ���������̃J������]�p�x
	XMFLOAT3 cameraDirection;	// �J�����̕����x�N�g��
};
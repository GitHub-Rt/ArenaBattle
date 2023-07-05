#pragma once
#include "CharacterBase.h"

class PolyLine;
class PlayerEffect;
class PlayerGauge;

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
	MaxDamageTimer = 10
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
	void OnCollision(GameObject* pTarget, Collider* nowCollider) override;

	// �J��������
	void NormalCamera();	// �ʏ펞�J�����֐�
	
	// �U������
	void NormalAttackAction();	// �ʏ�U���A�N�V����
	void HardAttackAction();	// ���U���A�N�V����

	// ��_���[�W���[�V��������
	void DamageMotion();
	void SetDamageDirection(XMVECTOR dir) { vTraveling = dir; }

	// HP�Q�[�W����
	void HPDamage(float value);		// HP�Q�[�W�����Ahp����
	void HPRecovery(float value);	// HP�Q�[�W�����Ahp����
	
	// ���͂̎�t���s�����ǂ���
	void SetInputReception(bool nextState) { isInputReception = nextState; }
	bool IsInputReception() { return isInputReception; }

	// �e���͂��s��ꂽ���ǂ���
	bool IsMoveEntry();			// ��������̓���
	bool IsDodEntry();			// �������̓���
	bool IsAttackEntry();		// �U������̓���
	bool IsRecoverEntry();		// �񕜎���̓���
	bool IsJumpEntry();			// �W�����v����̓���

#ifdef _DEBUG

	float GetHP() { return hp; }

	

#endif

private:

	// InternalDataCSV����l���i�[����萔
	float STRENGTH_RATE_INCREASING_ATTACK;	// �U���͂���������̗͂̊������C��
	float ATTACK_POWER_INCREASE_RATE;		// �̗͂̊������C�����̗͂����ɂȂ����Ƃ��̍U���͂̑�����
	float NORMAL_ATTACK_INCREASE_RATE;		// �ʏ�U���̍U���{��
	float HARD_ATTACK_INCREASE_RATE;		// ���U���̍U���{��
	float NORMAL_ATTACK_TIME;				// �ʏ�U���̍U������
	float HARD_ATTACK_TIME;					// ���U���̍U������
	float DODGE_TIME;						// �������
	float RECOVERY_POTION_NUMBER;			// �񕜃|�[�V�����̍ő吔
	float RECOVERY_QUANTITY;				// �񕜗�
	float MAX_DAMAGE_TIMER;					// ��_���[�W�ő厞��

	// �|�C���^
	PlayerGauge* pGauge;

	// �S�̕ϐ�
	float hp;		// �̗�

	// ���͎���̕ϐ�
	bool isTrrigerReset;		// ����̓��͂����Z�b�g�������ǂ���
	bool isInputReception;		// ���͂��󂯕t���邩�ǂ���

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

	// ��_���[�W����̕ϐ�
	int damageTimer;				// �_���[�W�^�C�}�[
	XMVECTOR vTraveling;			// �i�s�����x�N�g��

	// �J��������̕ϐ�
	float angleX;				// ���������̃J������]�p�x
	float angleY;				// ���������̃J������]�p�x
	XMFLOAT3 cameraDirection;	// �J�����̕����x�N�g��
};
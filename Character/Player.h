#pragma once
#include "CharacterBase.h"

class PolyLine;
class Effect;
class PlayerGauge;
class RecoveryPotion;
class Shadow;

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
	bool DiedAction() override;

	// �J��������
	void NormalCamera();	// �ʏ펞�J�����֐�
	XMFLOAT3 GetCameraDirection() { return cameraDirection; }	// �J�����̕����x�N�g����Ԃ�
	XMFLOAT3 GetCameraPosition() { return cameraPosition; }	    // �J�����̃|�W�V������Ԃ�
	XMFLOAT3 GetCameraFocas() { return cameraFocus; }			// �J�����̏œ_��Ԃ�
	
	// �U������
	void NormalAttackAction();	// �ʏ�U���A�N�V����
	void HardAttackAction();	// ���U���A�N�V����
	AttackState GetAttackState() { return attackState; }	// �U����Ԃ�Ԃ�

	// ��_���[�W���[�V��������
	void DamageMotion();
	void SetDamageDirection(XMVECTOR dir) { vTraveling = dir; }	// �_���[�W���̈ړ��������Z�b�g����

	// HP����
	float GetHP() { return hp; }	// HP��Ԃ�
	void HPDamage(float value);		// HP�Q�[�W�����Ahp����
	void HPRecovery(float value);	// HP�Q�[�W�����Ahp����
	
	// ���͂̎�t����
	void SetInputReception(bool nextState) { isInputReception = nextState; }	// ���͂̎�t�̗L�����Z�b�g����
	bool IsInputReception() { return isInputReception; }						// ���ݓ��͂��󂯕t���Ă��邩�ǂ�����Ԃ�

	// �e���͂��s��ꂽ���ǂ���
	bool IsMoveEntry();			// ��������̓���
	bool IsDodEntry();			// �������̓���
	bool IsAttackEntry();		// �U������̓���
	bool IsRecoverEntry();		// �񕜎���̓���
	bool IsJumpEntry();			// �W�����v����̓���

	// �~�̒[�܂Ŕ�΂�����
	void BlowAway();

#ifdef _DEBUG	// �f�o�b�O�֐�

	// �s���ɂ���
	void Immortality() { isImmortality = true; }	

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

	Shadow* pShadow;

	// �̗͎���̕ϐ�
	PlayerGauge* pGauge;
	RecoveryPotion* pPotion;
	int hRecoveryEffect;
	float hp;

	// ���͎���̕ϐ�
	bool isTrrigerReset;
	bool isInputReception;

	// �ړ�����̕ϐ�
	XMFLOAT3 movingDistance;
	XMVECTOR vPrevPos;

	// �W�����v����̕ϐ�
	float beforeJumpY;
	float jumpSpeed;
	bool isJumpSummit;

	// �U������̕ϐ�
	Effect* pEffect;
	AttackState attackState;
	int attackTimer;
	XMVECTOR attackVector;

	// �������̕ϐ�
	PolyLine* pLine;
	int dodgeTimer;

	// ��_���[�W����̕ϐ�
	int damageTimer;
	XMVECTOR vTraveling;

	// �J��������̕ϐ�
	float angleX;				// ���������̃J������]�p�x
	float angleY;				// ���������̃J������]�p�x
	XMFLOAT3 cameraDirection;
	XMFLOAT3 cameraPosition;
	XMFLOAT3 cameraFocus;


#ifdef _DEBUG	// �f�o�b�O�ϐ�

	bool isImmortality;	// �s�����ǂ���

#endif
};
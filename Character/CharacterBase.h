#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Model.h"
#include "../Engine/CsvReader.h"

#include <cmath>
#include <corecrt_math_defines.h>

// 180�x��\���萔
const double DEGREES_180 = 180.0;

enum class SCENE_ID;

// �L�����X�e�[�^�X
enum class CharacterStatus
{
	HP,				// �ő�̗�
	AttackPower,	// �U����
	DefensePower	// �h���
};

// �L�����p�����[�^
struct Parameters
{
	float hp;
	int attack;
	int defense;
};

// �L�����N�^�[ID
enum class CharacterID
{
	Player,
	Robot,
	NormalEnemy,
	EnemyBoss
};

// �L�����N�^�[�̏�Ԃ��Ǘ�
enum class CharacterState
{
	Idle,		// �ҋ@
	Moving,		// �ړ�
	Attacking,	// �U��
	Damaged,	// ��_���[�W
};

// �U���i�K���Ǘ�
enum class AttackStage
{
	NoAttack,		// �U����Ԃ͂Ȃ�
	StartAttack,	// �U���J�n
	Attack,			// �U����
	EndAttack		// �U���I��
};

// ��_���[�W�i�K���Ǘ�
enum class DamageStage
{
	NoDamage,       // �_���[�W�𕉂��ĂȂ�
	DamageStart,    // �_���[�W�𕉂��n��
	TakeDamage,     // �_���[�W�𕉂��Ă���(�_���[�W���[�V�������s��)
	EndDamage       // ���[�V�����I���
};

class CharacterBase : public GameObject
{
public:
	CharacterBase(GameObject* parent, std::string fileName);
	~CharacterBase();
	void Update() override;
	void Draw() override;
	

	/// <summary>
	/// �L�����N�^�[���f����Load����֐�
	/// </summary>
	/// <param name="fileName"></param>
	void CharacterModelLoad(std::string fileName);

	/// <summary>
	/// �L�����N�^�[�ɓ����蔻���ǉ�����֐�
	/// </summary>
	void CharacterAddCollider(XMFLOAT3 size, XMFLOAT3 center = XMFLOAT3(0,0,0));

	/// <summary>
	/// �}�e���A���̐F��ύX����֐�
	/// </summary>
	/// <param name="red">R�̒l</param>
	/// <param name="green">G�̒l</param>
	/// <param name="blue">B�̒l</param>
	void ColorChange(float red, float green, float blue);

	/// <summary>
	/// ���X�̃}�e���A���̐F�ɖ߂��֐�
	/// </summary>
	void RestoreOriginalColor();

	/// <summary>
	/// �L�����N�^�[��Draw����֐�
	/// </summary>
	/// <param name="charaModel"></param>
	void CharacterDraw(int charaModel);


	/// <summary>
	/// �_���[�W�v�Z���s����_���[�W�L�����Ƀ_���[�W���󂯂����Ƃ�ʒm����֐�
	/// </summary>
	/// <param name="attackChara">�U�����s�����L�����N�^�[��ID</param>
	/// <param name="target">�U�����󂯂��L�����N�^�[ID</param>
	/// <param name="magnification">�_���[�W�{��</param>
	void CharacterDamageCalculation(CharacterID attackChara, CharacterID target, float magnification = 1);

	/// <summary>
	/// �_���[�W�𕉂������Ƃ��Y���L�����N�^�[�ɒm�点��֐�
	/// </summary>
	/// <param name="target">�Y���L�����N�^�[��ID</param>
	/// <param name="attackDamage">�^����_���[�W��</param>
	void SetTakeDamageStart(CharacterID target, float attackDamage);

	/// <summary>
	/// �_���[�W�i�K��ύX����֐�
	/// </summary>
	/// <param name="nextStage"></param>
	void SetDamageStage(DamageStage nextStage) 
	{
		damageStage = nextStage; 
		characterState = CharacterState::Damaged;
	}

	/// <summary>
	/// �Y���L�����N�^�[���󂯂�_���[�W�ʂ��Z�b�g����
	/// </summary>
	/// <param name="attackDamage"></param>
	void SetDamage(float attackDamage) { damage = attackDamage; }

	/// <summary>
	/// �p�����[�^�ɒl���Z�b�g����֐�
	/// </summary>
	/// <param name="hp_"></param>
	/// <param name="attack_"></param>
	/// <param name="defense_"></param>
	void SetParameter(int hp_, int attack_, int defense_);

	/// <summary>
	/// �L�����N�^�[�̃��f���ԍ����擾����֐�
	/// </summary>
	/// <returns></returns>
	int GetCharacterModel() { return hModel; }

	/// <summary>
	/// �󂯂�_���[�W�ʂ�Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetDamage() { return damage; }

	/// <summary>
	/// ��Ԃ�ω�������
	/// </summary>
	/// <param name="nextState">���̏��</param>
	void ChangeState(CharacterState nextState) { characterState = nextState; }

	/// <summary>
	/// �L�����N�^�[�̏�Ԃ��擾����֐�
	/// </summary>
	/// <returns></returns>
	CharacterState GetCharacterState() { return characterState; }

	/// <summary>
	/// �e�V�[���ɑΉ��������C�̋�����Ԃ��֐�
	/// </summary>
	/// <param name="position">�I�u�W�F�N�g�̌��݈ʒu</param>
	/// <returns>���C�̋���</returns>
	float PositionAdjustment(XMFLOAT3 position);

	/// <summary>
	/// �Y���L�����N�^�[�̃o�����[�^�[���擾����֐�
	/// </summary>
	/// <param name="id">�Y���L�����N�^�[��ID</param>
	/// <returns></returns>
	Parameters GetParameter(CharacterID id);

	/// <summary>
	/// �Y���L�����N�^�[�̃p�����[�^����ݒ肷��֐�
	/// </summary>
	/// <param name="id">�L�����N�^�[ID</param>
	void SetParameter(CharacterID id);

	/// <summary>
	/// �Y���L�����N�^�[�̊Y�������擾����
	/// </summary>
	/// <param name="id">�L�����N�^�[ID</param>
	/// <param name="status">�L�����N�^�[�X�e�[�^�X</param>
	/// <returns>�Y�����</returns>
	int GetParameterValue(CharacterID id, CharacterStatus status);

	/// <summary>
	/// �Y���L�����N�^�[�̓����f�[�^�l���l������ϐ�
	/// </summary>
	/// <param name="id">�Y���L�����N�^�[ID</param>
	/// /// /// <param name="cal">�擾�������v�f�̗�</param>
	/// <returns></returns>
	float GetInternalData(CharacterID id, int cal);

	/// <summary>
	/// �����f�[�^�̃L�����N�^�[�̗�(�f�[�^��)��Ԃ��֐�
	/// </summary>
	/// <param name="id">�Y���L�����N�^�[ID</param>
	/// <returns></returns>
	int GetColumnCalCount(CharacterID id);

	/// <summary>
	/// �ړ��\�͈͓����ǂ�����Ԃ�
	/// </summary>
	/// <param name="position">�|�W�V����</param>
	/// <returns>�͈͊O�Ȃ�true</returns>
	bool IsMoveLimit(XMFLOAT3 position);


	/// <summary>
	/// �萔�Ƃ��Ĉ����f�[�^������������֐�
	/// </summary>
	virtual void SetData() = 0;

	/// <summary>
	/// �L�����N�^�[��HP���̊֐�
	/// </summary>
	virtual void CharacterCheckHP() = 0;

	/// <summary>
	/// �e�L�����N�^�[��Idle��Ԃ̂Ƃ��̏����������֐�
	/// </summary>
	virtual void CharacterUpdate() = 0;

	/// <summary>
	/// �e�L�����̈ړ����菈���������֐�
	/// </summary>
	virtual void CharacterMove() = 0;

	/// <summary>
	/// �e�L�����U�������������֐�
	/// </summary>
	virtual void CharacterAttack() = 0;

	/// <summary>
	/// �e�L�����̔�_���[�W���̏����������֐�
	/// </summary>
	virtual void CharacterTakeDamage(float damage) = 0; 


	


private:

	//�e�p�����[�^�̒l���擾����֐�
	int GetPlayerStatusValue(CharacterStatus status);
	int GetRobotStatusValue(CharacterStatus status);			
	int GetNormalEnemyStatusValue(CharacterStatus status);		
	int GetBossEnemyStatusValue(CharacterStatus status);

	int hModel;			// ���f���n���h��
	int groundHundle;	// �X�e�[�W���f���n���h��
	int value;			// �L�����N�^�[�̃p�����[�^���l
	float internalData; // �L�����N�^�[�̓����f�[�^�̐��l
	int calCount;		// �L�����N�^�[�����f�[�^�̗�
	float damage;		// �󂯂�_���[�W��
	float attackDamage;	// �^����_���[�W��
	CsvReader ParameterCSV;
	CsvReader PlayerInternalDataCSV;
	CsvReader RobotInternalDataCSV;
	Parameters parameter;

	CharacterState characterState;
	AttackStage attackStage;
	DamageStage damageStage;
};


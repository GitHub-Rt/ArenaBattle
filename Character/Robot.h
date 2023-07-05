#pragma once
#include "CharacterBase.h"

class Player;

// �����f�[�^���i�[���Ă���CSV�t�@�C���̊Y�����ڂɑΉ������s�����Ǘ�����
enum class RobotData
{
	BulletTimer = 1
};

// ���{�b�g���Ǘ�����N���X
class Robot : public CharacterBase
{
public:

	float GetAttackValue() { return GetParameterValue(CharacterID::Robot, CharacterStatus::AttackPower); }


	void SetData() override;
	Robot(GameObject* parent);
	~Robot();
	void Initialize()  override;
	void Release() override;
	void CharacterUpdate() override;
	void CharacterIdleAction() override;
	void CharacterMove() override;
	void CharacterAttack() override;

	void CharacterCheckHP() override {};
	void CharacterJumpAction()override {};
	void CharacterDodingAction()override {};
	void CharacterStunAction() override {};
	void CharacterTakeDamage(float damage) override {};
	void DrawEffect() override {};

	//�@�v���C���[�̃J�����������Ƀ��f������]������(�e�̑ł��������߂�)
	void SetAngle();

private:
	
	// InternalDataCSV����l���i�[����ϐ�
	int BETWEEN_BULLETTIMER;			// �e�����˂���Ԋu

	Player* pPlayer;
	int bulletTimer;
};


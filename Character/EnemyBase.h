#pragma once
#include "CharacterBase.h"
class EnemyBase : public CharacterBase
{
public:
	EnemyBase(GameObject* parent, std::string fileName);
	~EnemyBase();

	void CharacterUpdate() override;
	void Release() override;
	

	// Enemy���s��Ȃ��A�N�V����
	void CharacterJumpAction() override;
	void CharacterDodingAction() override;

	// Enemy��Update�֐�
	virtual void EnemyUpdate() = 0;


	// Enemy��Release�֐�
	virtual void EnemyRelease() = 0;
};


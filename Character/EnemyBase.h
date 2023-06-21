#pragma once
#include "CharacterBase.h"
class EnemyBase : public CharacterBase
{
public:
	EnemyBase(GameObject* parent, std::string fileName);
	~EnemyBase();

	void Release() override;
	

	// Enemy���s��Ȃ��A�N�V����
	void CharacterJumpAction() override;
	void CharacterDodingAction() override;


	// Enemy��Release�֐�
	virtual void EnemyRelease() = 0;
};


#pragma once
#include "CharacterBase.h"

class Player : public CharacterBase
{
public:
	void SetData() override;
	Player(GameObject* parent);
	~Player();
	void Initialize()  override;
	void Release() override;
	void CharacterUpdate() override;
	void CharacterMove() override;
	void CharacterAttack() override;
	void CharacterCheckHP() override;
	void CharacterTakeDamage(float damage) override;

private:
};
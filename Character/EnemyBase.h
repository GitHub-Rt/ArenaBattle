#pragma once
#include "CharacterBase.h"
class EnemyBase : public CharacterBase
{
public:
	EnemyBase(GameObject* parent, std::string fileName);
	~EnemyBase();

	void CharacterUpdate() override;
	void Release() override;
	

	// Enemyが行わないアクション
	void CharacterJumpAction() override;
	void CharacterDodingAction() override;

	// EnemyのUpdate関数
	virtual void EnemyUpdate() = 0;


	// EnemyのRelease関数
	virtual void EnemyRelease() = 0;
};


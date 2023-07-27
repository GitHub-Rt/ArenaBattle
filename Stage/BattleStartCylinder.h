#pragma once
#include "StageBase.h"

class PlayScene;

class BattleStartCylinder : public StageBase
{
public:

	BattleStartCylinder(GameObject* parent);
	~BattleStartCylinder();
	void Initialize() override;
	void Draw() override;
	void OnCollision(GameObject* pTarget, Collider* nowCollider) override;

private:

	PlayScene* pScene;

};


#pragma once
#include "AttackModelBase.h"

class EnemyBossJumpArea : public AttackModelBase
{
public:
	EnemyBossJumpArea(GameObject* parent);
	~EnemyBossJumpArea();
	void Initialize() override;
	void AttackModelUpdate() override;
	void Draw() override;

	// 可視化させるための準備
	void SetArea(XMFLOAT3 pos);
	

private:
	Transform moveArea;

	int hModelFloor;	// 床のモデルハンドル
	int hModelCircle;	// 動かす円のモデルハンドル

	int scaleTimer;		// 拡縮計測タイマー
};


#pragma once
#include "CharacterBase.h"


// 攻撃の状態を管理
enum class AttackState
{
	NoAttack,
	NormalAttack,
	HardAttack
};

// 内部データを格納しているCSVファイルの該当項目に対応した行数を管理する
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
	MaxInvincibleTime = 10
};

class Player : public CharacterBase
{
public:

	// カメラの方向ベクトルを返す
	XMFLOAT3 GetCameraDirection() { return cameraDirection; }

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
	void CharacterTakeDamage(float damage) override;
	void CharacterCheckHP() override;


	// カメラ周り
	void NormalCamera();	// 通常時カメラ関数
	

	// 各入力が行われたかどうか
	bool IsMoveEntry();			// 動き周りの入力
	bool IsDodEntry();			// 回避周りの入力
	bool IsAttackEntry();		// 攻撃周りの入力
	bool IsRecoverEntry();		// 回復周りの入力
	bool IsJumpEntry();			// ジャンプ周りの入力

private:

	// InternalDataCSVから値を格納する変数
	float STRENGTH_RATE_INCREASING_ATTACK;	// 攻撃力が増加する体力の割合ライン
	float ATTACK_POWER_INCREASE_RATE;		// 体力の割合ラインより体力が下になったときの攻撃力の増加率
	float NORMAL_ATTACK_INCREASE_RATE;		// 通常攻撃の攻撃倍率
	float HARD_ATTACK_INCREASE_RATE;		// 強攻撃の攻撃倍率
	float NORMAL_ATTACK_TIME;				// 通常攻撃の攻撃時間
	float HARD_ATTACK_TIME;					// 強攻撃の攻撃時間
	float DODGE_TIME;						// 回避時間
	float RECOVERY_POTION_NUMBER;			// 回復ポーションの最大数
	float RECOVERY_QUANTITY;				// 回復量
	int MAX_INVINCIBLE_TIME;				// 最大無敵時間

	// 状態変数
	AttackState attackState;

	// 入力周りの変数
	bool isTrrigerReset;

	// 移動周りの変数
	XMFLOAT3 movingDistance;	// 移動量
	XMVECTOR vPrevPos;			// 前回の位置ベクトル

	// カメラ周りの変数
	float angleX;				// 水平方向のカメラ回転角度
	float angleY;				// 鉛直方向のカメラ回転角度
	XMFLOAT3 cameraDirection;	// カメラの方向ベクトル
};
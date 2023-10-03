#pragma once
#include "CharacterBase.h"

class PolyLine;
class Effect;
class PlayerGauge;
class RecoveryPotion;
class Shadow;

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

	// カメラ周り
	void NormalCamera();	// 通常時カメラ関数
	XMFLOAT3 GetCameraDirection() { return cameraDirection; }	// カメラの方向ベクトルを返す
	XMFLOAT3 GetCameraPosition() { return cameraPosition; }	    // カメラのポジションを返す
	XMFLOAT3 GetCameraFocas() { return cameraFocus; }			// カメラの焦点を返す
	
	// 攻撃周り
	void NormalAttackAction();	// 通常攻撃アクション
	void HardAttackAction();	// 強攻撃アクション
	AttackState GetAttackState() { return attackState; }	// 攻撃状態を返す

	// 被ダメージモーション周り
	void DamageMotion();
	void SetDamageDirection(XMVECTOR dir) { vTraveling = dir; }	// ダメージ時の移動方向をセットする

	// HP周り
	float GetHP() { return hp; }	// HPを返す
	void HPDamage(float value);		// HPゲージ減少、hp減少
	void HPRecovery(float value);	// HPゲージ増加、hp増加
	
	// 入力の受付周り
	void SetInputReception(bool nextState) { isInputReception = nextState; }	// 入力の受付の有無をセットする
	bool IsInputReception() { return isInputReception; }						// 現在入力を受け付けているかどうかを返す

	// 各入力が行われたかどうか
	bool IsMoveEntry();			// 動き周りの入力
	bool IsDodEntry();			// 回避周りの入力
	bool IsAttackEntry();		// 攻撃周りの入力
	bool IsRecoverEntry();		// 回復周りの入力
	bool IsJumpEntry();			// ジャンプ周りの入力

	// 円の端まで飛ばす処理
	void BlowAway();

#ifdef _DEBUG	// デバッグ関数

	// 不死にする
	void Immortality() { isImmortality = true; }	

#endif

private:

	// InternalDataCSVから値を格納する定数
	float STRENGTH_RATE_INCREASING_ATTACK;	// 攻撃力が増加する体力の割合ライン
	float ATTACK_POWER_INCREASE_RATE;		// 体力の割合ラインより体力が下になったときの攻撃力の増加率
	float NORMAL_ATTACK_INCREASE_RATE;		// 通常攻撃の攻撃倍率
	float HARD_ATTACK_INCREASE_RATE;		// 強攻撃の攻撃倍率
	float NORMAL_ATTACK_TIME;				// 通常攻撃の攻撃時間
	float HARD_ATTACK_TIME;					// 強攻撃の攻撃時間
	float DODGE_TIME;						// 回避時間
	float RECOVERY_POTION_NUMBER;			// 回復ポーションの最大数
	float RECOVERY_QUANTITY;				// 回復量
	float MAX_DAMAGE_TIMER;					// 被ダメージ最大時間

	Shadow* pShadow;

	// 体力周りの変数
	PlayerGauge* pGauge;
	RecoveryPotion* pPotion;
	int hRecoveryEffect;
	float hp;

	// 入力周りの変数
	bool isTrrigerReset;
	bool isInputReception;

	// 移動周りの変数
	XMFLOAT3 movingDistance;
	XMVECTOR vPrevPos;

	// ジャンプ周りの変数
	float beforeJumpY;
	float jumpSpeed;
	bool isJumpSummit;

	// 攻撃周りの変数
	Effect* pEffect;
	AttackState attackState;
	int attackTimer;
	XMVECTOR attackVector;

	// 回避周りの変数
	PolyLine* pLine;
	int dodgeTimer;

	// 被ダメージ周りの変数
	int damageTimer;
	XMVECTOR vTraveling;

	// カメラ周りの変数
	float angleX;				// 水平方向のカメラ回転角度
	float angleY;				// 鉛直方向のカメラ回転角度
	XMFLOAT3 cameraDirection;
	XMFLOAT3 cameraPosition;
	XMFLOAT3 cameraFocus;


#ifdef _DEBUG	// デバッグ変数

	bool isImmortality;	// 不死かどうか

#endif
};
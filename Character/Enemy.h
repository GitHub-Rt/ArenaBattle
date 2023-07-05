#pragma once
#include "EnemyBase.h"

enum class AttackState;

enum class EnemyData
{
	AttackStartRange = 1,
	AttackTime = 2,
	DamageTimer = 3
};

class Enemy : public EnemyBase
{
public:
	Enemy(GameObject* parent);
	~Enemy();

	void SetData() override;
	void Initialize() override;
	void Draw() override;
	void EnemyRelease() override;
	void EnemyUpdate() override;
	void CharacterIdleAction() override;
	void CharacterMove() override;
	void CharacterAttack() override;
	void CharacterTakeDamage(float damage) override;
	void CharacterCheckHP() override;
	void OnCollision(GameObject* pTarget, Collider* nowCollider) override;


	void ModelRotate(XMVECTOR vMove);

	// 小ジャンプする関数
	void SmallJump();

	// 被ダメージモーション
	void DamageMotion();

	// プレイヤーに触れているかどうか
	bool IsPlayerHitting() { return isHittingPlayer; }

	void DrawEffect() override {};
	void CharacterStunAction() override {};

#ifdef _DEBUG

	bool isDamage;

	bool IsDamage() { return isDamage; }

	float GetHP() { return hp; }

#endif


private:

	// InternalDataCSVから値を格納する変数
	float ATTACK_START_RANGE;		// 攻撃開始する範囲の長さ
	int ATTACK_TIME;				// 攻撃時間
	int DAMAGE_TIME;				// ダメージ時間
	
	// 全体変数
	float hp;	// 体力
	int hModel;	// モデル番号

	// 移動周りの変数
	XMVECTOR vPrevPos;				// 前回の位置ベクトル

	// 攻撃周りの変数
	XMVECTOR vAttackMove;			// 攻撃時の移動ベクトル
	int attackTimer;				// 攻撃タイマー

	// 攻撃前ジャンプ周りの変数
	float beforeJumpY;				// ジャンプ前のy座標
	float jumpSpeed;				// 初速度
	bool isJumpSummit;				// ジャンプの頂上に到達したかどうか
	bool isStartingAttackMoving;	// ジャンプ処理を終えて移動を始めたかどうか

	// 被ダメージ周りの変数
	int damageTimer;				// ダメージ時間

	// その他
	bool isHittingPlayer;			// プレイヤーに触れているかどうか
};


#pragma once
#include "EnemyBase.h"

class Player;
class EnemyBossGauge;
class EnemyBossBullet;

enum class EnemyBossData
{
	EntryFirstPosY = 1,
	AttackIntervalTime,
	DamageTime,
	RateForMaxStrength,
	TotalDamagesUpAILevel,
	BulletAtkIntervalTime,
	BulletAtkMaxCount,
	BulletAtkMagnification,
	WavesAtkMaxCount,
	WavesAtkMagnification,
};

enum class BossAttackState
{
	NoAttack = (unsigned int)(1 << 0),
	BulletAttack = (unsigned int)(1 << 1),
	SpiralMoveAttack = (unsigned int)(1 << 2),
	WavesAttack = (unsigned int)(1 << 3),
	JumpAttack = (unsigned int)(1 << 4),
	SpecialAttack = (unsigned int)(1 << 5),
	MaxAttackState
};

enum class BossAttackModelHandle
{
	Bullet,
	Wave,
};

enum class BossAIState
{
	Allowance = 1,	// 油断(余裕)状態
	Normal,			// 通常状態
	Caution			// 警戒(臨戦)状態
};

class EnemyBoss : public EnemyBase
{
public:

	EnemyBoss(GameObject* parent);
	~EnemyBoss();

	void SetData() override;
	void Initialize() override;
	void EnemyRelease() override;
	void EnemyUpdate() override;
	void CharacterIdleAction() override;
	void CharacterMove() override {};
	void CharacterAttack() override;
	void CharacterTakeDamage(float damage) override;
	void CharacterCheckHP() override;
	void DrawEffect() override;
	void CharacterStunAction() override;
	void OnCollision(GameObject* pTarget, Collider* nowCollider) override;

	// 攻撃種類の選択
	void AttackTypeSelection();

	// 攻撃状態周りの関数
	// 攻撃状態を立てる
	void ChangeAttackState(BossAttackState nextState);

	// 攻撃状態を伏せる
	void ClearAttackState(BossAttackState state);
	
	// どの攻撃状態も立っていなかったらNoAttackに変更する
	void ChangeForNoAttack();

	// 攻撃状態の取得(状態が立っていたらtrue)
	bool IsAttackState(BossAttackState state) { return (bossAttackState & (unsigned int)state) != 0; }

	// 攻撃モデルとプレイヤーのダメージ処理
	void AttackModelDamageToPlayer(BossAttackModelHandle attackSource, XMVECTOR vec);

	// 各攻撃の関数

	void BulletAttackAction();
	// 弾攻撃に必要な計算を行いスタートさせる関数
	void BulletAttackCal(std::string dirName);
	void SpiralMoveAttackAction();
	void WavesAttackAction();
	void JumpAttackAction();
	void SpecialAttackAction();

	// 各攻撃変数のリセット
	void AttackVariableReset(BossAttackState nowState);

	void Damage(float damage);
	void DamageMotion();

	// EnemyBoss登場処理(登場が終わったらtrueを返す)
	bool BossEntry();

	// Update等の処理を開始する関数
	void ProcessStart();


	// 初期位置周辺に戻ってきたかどうか(戻ってきたらtrue)
	bool IsFirstPosAround(XMFLOAT3 pos);

#ifdef  _DEBUG

	float GetHP() { return hp; }

#endif


private:
	
	// InternalDataから取得する定数
	float ENTRY_FIRST_POS_Y;		// 初期y座標
	int ATTACK_INTERVAL_TIME;		// 攻撃間隔時間
	int DAMAGE_TIME;				// 被ダメージ時間
	int RATE_FOR_MAX_STRENGTH;		// 特殊攻撃を行う際の最大体力に対する割合
	int TOTAL_DAMAGES_UP_AI_LEVEl;	// AIレベルを上げる合計ダメージ量
	int BULLET_ATK_INTERVAL_TIME;	// 弾攻撃の間隔時間
	int BULLET_ATK_MAX_COUNT;		// 弾攻撃の最大回数
	float BULLET_ATK_MAGNIFICATION;	// 弾攻撃の倍率
	int WAVES_ATK_MAX_COUNT;		// 波状攻撃の最大回数
	float WAVES_ATK_MAGNIFICATION;	// 波状攻撃の倍率

	// その他の定数
	float ENTRY_POS_Y;				// 着地時のy座標
	
	
	// 全体変数
	Player* pPlayer;
	unsigned int bossAttackState;
	BossAIState bossAIState;
	XMFLOAT3 firstPos;

	// 攻撃全体周りの変数
	int attackIntervalTimer;
	
	// 弾攻撃周りの変数
	int bulletTimer;	// 攻撃間隔
	int bulletCount;	// 攻撃回数


	// 渦巻移動攻撃周りの変数
	float spiralAngle;		// 回転角度
	float spiralRadius;		// 半径
	bool isEndLine;			// 端に到達したかどうか


	// 波状攻撃の変数
	int wavesCount;			// 攻撃回数
	float wavesJumpSpeed;	// 波状攻撃前の上昇変数
	int wavesJumpTimer;		// 上昇時間


	// ジャンプ攻撃周りの変数


	// 特殊攻撃周りの変数
	bool isSpecialAttack;	// 特殊攻撃を行ったかどうか


	// 体力周りの変数
	EnemyBossGauge* pGauge;
	float maxHp;
	float hp;

	// 登場演出周りの変数
	bool isWarningStart;

	// 被ダメージ周りの変数
	int damageTimer;
	float totalDamages;
};


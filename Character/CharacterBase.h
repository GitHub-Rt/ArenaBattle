#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Model.h"
#include "../Engine/CsvReader.h"

#include "../Manager/EnemyManager.h"

#include <cmath>
#include <corecrt_math_defines.h>

// 180度を表す定数
const double DEGREES_180 = 180.0;
enum class SCENE_ID;

// キャラステータス
enum class CharacterStatus
{
	HP,				// 最大体力
	AttackPower,	// 攻撃力
	DefensePower	// 防御力
};

// キャラパラメータ
struct Parameters
{
	float hp;
	int attack;
	int defense;
};

// キャラクターID
enum class CharacterID
{
	Player,
	Robot,
	NormalEnemy,
	EnemyBoss
};

// キャラクターの状態を管理
enum class CharacterState
{
	Idle =(unsigned int)( 1 << 0),        // 待機		00000001 1
	Moving = (unsigned int)(1 << 1),      // 移動		00000010 2
	Attacking = (unsigned int)(1 << 2),   // 攻撃		00000100 4
	Damaged = (unsigned int)(1 << 3),     // 被ダメージ 00001000 8
	Dodging = (unsigned int)(1 << 4),     // 回避		00010000 16
	Jumping = (unsigned int)(1 << 5),     // ジャンプ	00100000 32
	Stan = (unsigned int)(1 << 6),		  // スタン		01000000 64
	MAX_CharacterState
};

// 攻撃段階を管理
enum class AttackStage
{
	NoAttack,		// 攻撃状態はない
	StartAttack,	// 攻撃開始
	Attack,			// 攻撃中
	EndAttack		// 攻撃終了
};

// 被ダメージ段階を管理
enum class DamageStage
{
	NoDamage,       // ダメージを負ってない
	DamageStart,    // ダメージを負い始め
	TakeDamage,     // ダメージを負っている(ダメージモーションを行う)
	EndDamage       // モーション終わり
};

class CharacterBase : public GameObject
{
public:
	CharacterBase(GameObject* parent, std::string fileName);
	~CharacterBase();
	void Update() override;
	void Draw() override;
	

	/// <summary>
	/// キャラクターモデルをLoadする関数
	/// </summary>
	/// <param name="fileName"></param>
	void CharacterModelLoad(std::string fileName);

	/// <summary>
	/// モデル番号を返す
	/// </summary>
	/// <returns></returns>
	int GetCharacterModelHandle() { return hModel; }

	/// <summary>
	/// キャラクターに当たり判定を追加する関数
	/// </summary>
	void CharacterAddCollider(XMFLOAT3 size, XMFLOAT3 center = XMFLOAT3(0,2,0));

	/// <summary>
	/// マテリアルの色を変更する関数
	/// </summary>
	/// <param name="red">Rの値</param>
	/// <param name="green">Gの値</param>
	/// <param name="blue">Bの値</param>
	/// /// <param name="alpha">透明度</param>
	void ColorChange(float red, float green, float blue, float alpha = 1);

	/// <summary>
	/// 元々のマテリアルの色に戻す関数
	/// </summary>
	void RestoreOriginalColor();

	/// <summary>
	/// マテリアルを赤に変化させる
	/// </summary>
	void ChangeDamageColor(bool isDamage = true);

	/// <summary>
	/// キャラクターをDrawする関数
	/// </summary>
	/// <param name="charaModel"></param>
	void CharacterDraw(int charaModel);


	/// <summary>
	/// ダメージ計算を行い被ダメージキャラにダメージを受けたことを通知する関数
	/// </summary>
	/// <param name="attackChara">攻撃を行ったキャラクターのID</param>
	/// <param name="target">攻撃を受けたキャラクターID</param>
	/// <param name="indexNumber">どのEnemyかを判別させるため(基本的にはsize + 1)</param>
	/// <param name="magnification">ダメージ倍率</param>
	void CharacterDamageCalculation(CharacterID attackChara, CharacterID target, int indexNumber = EnemyManager::GetVectorSize() + 1, float magnification = 1);

	/// <summary>
	/// ダメージ量を該当キャラクターにセットする関数
	/// </summary>
	/// <param name="target">該当キャラクターのID</param>
	/// <param name="attackDamage">与えるダメージ量</param>
	/// <param name="indexNumber">どのEnemyかを判別させるため(基本的にはsize + 1)</param>
	void SetTakeDamageStart(CharacterID target, float attackDamage, int indexNumber = EnemyManager::GetVectorSize() + 1);

	/// <summary>
	/// ダメージ段階を変更する関数
	/// </summary>
	/// <param name="nextStage"></param>
	void SetDamageStage(DamageStage nextStage) 
	{
		damageStage = nextStage; 
		ChangeState(CharacterState::Damaged);
	}

	/// <summary>
	/// ダメージ段階を取得する関数
	/// </summary>
	/// <returns></returns>
	DamageStage GetDamageState() { return damageStage; }

	/// <summary>
	/// 該当キャラクターが受けるダメージ量をセットする
	/// </summary>
	/// <param name="attackDamage"></param>
	void SetDamage(float attackDamage) { damage = attackDamage; }

	/// <summary>
	/// パラメータに値をセットする関数
	/// </summary>
	/// <param name="hp_"></param>
	/// <param name="attack_"></param>
	/// <param name="defense_"></param>
	void SetParameter(int hp_, int attack_, int defense_);

	/// <summary>
	/// キャラクターのモデル番号を取得する関数
	/// </summary>
	/// <returns></returns>
	int GetCharacterModel() { return hModel; }

	/// <summary>
	/// 受けるダメージ量を返す
	/// </summary>
	/// <returns></returns>
	float GetDamage() { return damage; }

	/// <summary>
	/// 状態を変化させる(状態フラグを立てる)
	/// </summary>
	/// <param name="nextState">次の状態</param>
	void ChangeState(CharacterState nextState) 
	{
		characterStateFlg |= (unsigned int)nextState;

		if (IsStateSet(CharacterState::Idle) && nextState != CharacterState::Idle)
		{
			ClearState(CharacterState::Idle);
		}
	}

	/// <summary>
	/// 状態をクリアにする(状態フラグを下す)
	/// </summary>
	/// <param name="clearState"></param>
	void ClearState(CharacterState clearState) 
	{
		characterStateFlg &= ~(unsigned int)clearState;
		ChangeStateForIdle();
	}

	/// <summary>
	/// 待機以外の状態がすべてfalseだったら状態をIdleにする
	/// </summary>
	void ChangeStateForIdle();

	/// <summary>
	/// 状態を取得する(状態が立っているかどうかを返す)
	/// </summary>
	/// <param name="state"></param>
	/// <returns>状態が立っていたらtrue</returns>
	bool IsStateSet(CharacterState state) const { return (characterStateFlg & (unsigned int)state) != 0; }

	/// <summary>
	/// 方向ベクトルを正規化して返す関数
	/// </summary>
	/// <returns></returns>
	XMVECTOR GetFrontVector();

	/// <summary>
	/// 各シーンに対応したレイの距離を返す関数
	/// </summary>
	/// <param name="position">オブジェクトの現在位置</param>
	/// <returns>レイの距離</returns>
	float PositionAdjustment(XMFLOAT3 position);

	/// <summary>
	/// 該当キャラクターのバラメーターを取得する関数
	/// </summary>
	/// <param name="id">該当キャラクターのID</param>
	/// <returns></returns>
	Parameters GetParameter(CharacterID id);

	/// <summary>
	/// 該当キャラクターのパラメータ情報を設定する関数
	/// </summary>
	/// <param name="id">キャラクターID</param>
	void SetParameter(CharacterID id);

	/// <summary>
	/// 該当キャラクターの該当情報を取得する
	/// </summary>
	/// <param name="id">キャラクターID</param>
	/// <param name="status">キャラクターステータス</param>
	/// <returns>該当情報</returns>
	int GetParameterValue(CharacterID id, CharacterStatus status);

	/// <summary>
	/// 該当キャラクターの内部データ値を獲得する変数
	/// </summary>
	/// <param name="id">該当キャラクターID</param>
	/// /// /// <param name="cal">取得したい要素の列数</param>
	/// <returns></returns>
	float GetInternalData(CharacterID id, int cal);

	/// <summary>
	/// 内部データのキャラクターの列数(データ数)を返す関数
	/// </summary>
	/// <param name="id">該当キャラクターID</param>
	/// <returns></returns>
	int GetColumnCalCount(CharacterID id);

	/// <summary>
	/// 移動可能範囲内かどうかを返す
	/// </summary>
	/// <param name="position">ポジション</param>
	/// <returns>範囲外ならtrue</returns>
	bool IsMoveLimit(XMFLOAT3 position);


	/// <summary>
	/// 定数として扱うデータを初期化する関数
	/// </summary>
	virtual void SetData() = 0;

	/// <summary>
	/// キャラクターのHP回りの関数
	/// </summary>
	virtual void CharacterCheckHP() = 0;

	/// <summary>
	/// 各キャラクターの度の状態のときも実行したい処理をかく関数
	/// </summary>
	virtual void CharacterUpdate() = 0;

	/// <summary>
	/// キャラクターのIdle状態の処理を書く関数
	/// </summary>
	virtual void CharacterIdleAction() = 0;

	/// <summary>
	/// 各キャラの移動周り処理を書く関数
	/// </summary>
	virtual void CharacterMove() = 0;

	/// <summary>
	/// 各キャラ攻撃処理を書く関数
	/// </summary>
	virtual void CharacterAttack() = 0;

	/// <summary>
	/// 各キャラの被ダメージ時の処理を書く関数
	/// </summary>
	virtual void CharacterTakeDamage(float damage) = 0; 

	/// <summary>
	/// ジャンプアクション処理
	/// </summary>
	virtual void CharacterJumpAction() = 0;

	/// <summary>
	/// 回避アクション処理
	/// </summary>
	virtual void CharacterDodingAction() = 0;

	/// <summary>
	/// スタン中の処理
	/// </summary>
	virtual void CharacterStunAction() = 0;

	/// <summary>
	/// エフェクトの描画に使う
	/// </summary>
	virtual void DrawEffect() = 0;

private:

	//各パラメータの値を取得する関数
	int GetPlayerStatusValue(CharacterStatus status);
	int GetRobotStatusValue(CharacterStatus status);			
	int GetNormalEnemyStatusValue(CharacterStatus status);		
	int GetBossEnemyStatusValue(CharacterStatus status);

	int hModel;			// モデルハンドル
	int groundHundle;	// ステージモデルハンドル
	int value;			// キャラクターのパラメータ数値
	float internalData; // キャラクターの内部データの数値
	int calCount;		// キャラクター内部データの列数
	float damage;		// 受けるダメージ量

	// 各種データ
	CsvReader ParameterCSV;
	CsvReader PlayerInternalDataCSV;
	CsvReader RobotInternalDataCSV;
	CsvReader EnemyInternalDataCSV;
	CsvReader EnemyBossInternalDataCSV;
	Parameters parameter;

	unsigned int characterStateFlg;	// ビットフラグ
	AttackStage attackStage;
	DamageStage damageStage;
};


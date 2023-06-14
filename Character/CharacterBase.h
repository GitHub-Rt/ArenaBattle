#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Model.h"
#include "../Engine/CsvReader.h"

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
	Idle,		// 待機
	Moving,		// 移動
	Attacking,	// 攻撃
	Damaged,	// 被ダメージ
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
	/// キャラクターに当たり判定を追加する関数
	/// </summary>
	void CharacterAddCollider(XMFLOAT3 size, XMFLOAT3 center = XMFLOAT3(0,0,0));

	/// <summary>
	/// マテリアルの色を変更する関数
	/// </summary>
	/// <param name="red">Rの値</param>
	/// <param name="green">Gの値</param>
	/// <param name="blue">Bの値</param>
	void ColorChange(float red, float green, float blue);

	/// <summary>
	/// 元々のマテリアルの色に戻す関数
	/// </summary>
	void RestoreOriginalColor();

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
	/// <param name="magnification">ダメージ倍率</param>
	void CharacterDamageCalculation(CharacterID attackChara, CharacterID target, float magnification = 1);

	/// <summary>
	/// ダメージを負ったことを該当キャラクターに知らせる関数
	/// </summary>
	/// <param name="target">該当キャラクターのID</param>
	/// <param name="attackDamage">与えるダメージ量</param>
	void SetTakeDamageStart(CharacterID target, float attackDamage);

	/// <summary>
	/// ダメージ段階を変更する関数
	/// </summary>
	/// <param name="nextStage"></param>
	void SetDamageStage(DamageStage nextStage) 
	{
		damageStage = nextStage; 
		characterState = CharacterState::Damaged;
	}

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
	/// 状態を変化させる
	/// </summary>
	/// <param name="nextState">次の状態</param>
	void ChangeState(CharacterState nextState) { characterState = nextState; }

	/// <summary>
	/// キャラクターの状態を取得する関数
	/// </summary>
	/// <returns></returns>
	CharacterState GetCharacterState() { return characterState; }

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
	/// 各キャラクターのIdle状態のときの処理をかく関数
	/// </summary>
	virtual void CharacterUpdate() = 0;

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
	float attackDamage;	// 与えるダメージ量
	CsvReader ParameterCSV;
	CsvReader PlayerInternalDataCSV;
	CsvReader RobotInternalDataCSV;
	Parameters parameter;

	CharacterState characterState;
	AttackStage attackStage;
	DamageStage damageStage;
};


#pragma once

#include "../Engine/VFX.h"

enum class EmitterType
{
	Detonation = 0,	//爆破エフェクト
	Ventilation,	//風切りエフェクト
	Tornado,		//竜巻エフェクト
	Dead,			//死亡エフェクト
	MaxEmmierType
};


class Effect
{

public:

	Effect();
	void Release();

	void SetCalledDeadFlg() { isCalledDeadEffect = true; }
	bool IsCalledDeadEffect() { return isCalledDeadEffect; }

	//爆破エフェクトに関する関数

	/// <summary>
	/// 爆発エフェクトを出す関数
	/// </summary>
	void StartEffectDetonation();

	/// <summary>
	/// 爆破エフェクトを停止する関数
	/// </summary>
	void StopEffectDetonation();




	// 強攻撃エフェクトに関する関数

	/// <summary>
	/// 強攻撃エフェクトを開始する関数
	/// </summary>
	void StartEffectAtHardAttack();

	/// <summary>
	/// 強攻撃エフェクトを停止する関数
	/// </summary>
	void StopEffectAtHardAttack();




	// 通常攻撃エフェクト周り

	/// <summary>
	/// 通常攻撃エフェクトを開始する関数
	/// </summary>
	void StartEffectAtNormalAttack();

	/// <summary>
	/// 通常攻撃エフェクトを停止する関数
	/// </summary>
	void StopEffectAtNormalAttack();
	

	/// <summary>
	/// エフェクトの表示位置をセットする関数
	/// </summary>
	/// <param name="pos">エミッター位置</param>
	/// /// <param name="type">エフェクト種類</param>
	void SetEmitterPosition(XMFLOAT3 pos, EmitterType type);

	// 死亡エフェクト周りの関数

	/// <summary>
	/// 死亡エフェクトを開始する関数
	/// </summary>
	void StartEffectDead();

	/// <summary>
	/// 死亡エフェクトを停止する関数
	/// </summary>
	void StopEffectDead();

private:

	bool isCalledDeadEffect;

	// 爆破エフェクト回りの変数
	EmitterData data_Detonation;
	int eLimitFire;
	int eLimitSparks;
	int eLimitGround;

	// 竜巻エフェクト回りの変数
	EmitterData data_Tornado;
	int eLimitTornado;

	// 風切りエフェクト回りの変数
	XMFLOAT3 ventilationDir;
	XMFLOAT3 ventilationRotate;
	EmitterData data_Ventilation;
	int eLimitVentilation;

	// 死亡エフェクト周りの変数
	EmitterData data_Dead;
	int eLimitDead_smoke;
	int eLimitDead_bubble;
};


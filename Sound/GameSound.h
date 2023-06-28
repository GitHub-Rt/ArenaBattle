#pragma once
#include <string>

// ゲーム内音楽
enum class SoundTrack
{
	TitleSound = 0,	// タイトルシーン等の音楽
	PlaySceneSound,		// プレイシーンの音楽
	ButtleSound,	// ノーマル敵との戦闘音楽
	BossSound,		// ボス戦の戦闘音楽
	LastBossSound,	// 第2形態のボス戦の戦闘音楽
	ClearSound,		// クリア時の音楽
	GameOverSound,	// ゲームオーバーの音楽
	Alert,				// ボス登場演出時効果音
	MaxTrack		// ゲーム内音楽の最大数
};

// ゲーム内効果音
enum class SoundEffect
{
	Determinant = 0,	// 選択決定時効果音
	MoveSelection,		// 選択項目移動時効果音
	Touch,				// PlayScene内の黄色い筒に触れた時の効果音
	GaugeRecovery,		// 体力ゲージ回復時効果音
	NormalAttack,		// 通常攻撃時効果音
	HardAttack,			// 強攻撃時効果音
	Damage,				// 被ダメージ時効果音
	MaxEffect			// 効果音の最大数
};


class GameSound
{
public:
	GameSound();

	void Release();

	/// <summary>
	/// サウンド全体の再生情報をfalseにする関数
	/// </summary>
	void SetALLFalse()
	{
		SetSoundALLFalse();
		SetEffectALLFalse();
	}




	/////////      ゲーム内音楽の関数      //////////////



	/// <summary>
	/// 該当曲をロードする(無限ループ)
	/// </summary>
	/// <param name="trackNumber">該当曲の番号</param>
	/// <param name="volume">該当曲の音量(0～1の間)(省略可)</param>
	void SoundLoad(SoundTrack trackNumber, float volume = 1.0f);
	
	/// <summary>
	/// 該当曲をロードする(再生方式選択)
	/// </summary>
	/// <param name="trackNumber">該当曲の番号</param>
	/// <param name="isRoop">true→無限ループ、false→１度のみ</param>
	/// <param name="volume">該当曲の音量(0～1の間)(省略可)</param>
	int IntSoundLoad(SoundTrack trackNumber, bool isRoop, float volume = 1.0f);

	/// <summary>
	/// 該当曲の再生を行う
	/// </summary>
	/// <param name="track">該当曲の番号</param>
	void SoundPlay(SoundTrack trackNumber);
	
	/// <summary>
	/// 該当曲を停止する
	/// </summary>
	/// <param name="track">該当曲の番号</param>
	void SoundStop(SoundTrack trackNumber);

	/// <summary>
	/// 該当曲が１周したかどうかを調べる
	/// </summary>
	/// <param name="trackNumber">該当曲の番号</param>
	/// <param name="trackContents">該当曲の中身の番号</param>
	void SoundEnd(SoundTrack trackNumber, int trackContents);

	/// <summary>
	/// 該当曲が再生中かどうかを取得
	/// </summary>
	/// <param name="trackNumber">該当曲の番号</param>
	/// <returns>再生中はTrue</returns>
	bool GetSoundFlg(SoundTrack trackNumber) { return track[(int)trackNumber].isPlay; }

	/// <summary>
	/// すべての曲の再生情報をfalseにする
	/// </summary>
	void SetSoundALLFalse()
	{
		for (int i = 0; i < (int)SoundTrack::MaxTrack; i++)
		{
			if (GetSoundFlg((SoundTrack)i))
			{
				SoundStop((SoundTrack)i);
			}
		}
	}

	/// <summary>
	/// 該当曲の再生情報をFalseにする
	/// </summary>
	/// <param name="trackNumber">該当曲の番号</param>
	void SetSoundFalse(SoundTrack trackNumber)
	{
		if (track[(int)trackNumber].isPlay == false)
		{
			return;
		}
		track[(int)trackNumber].isPlay = false;
	}





	///////     ゲーム内効果音の関数    //////////

	/// <summary>
	/// 該当効果音をロードする
	/// </summary>
	/// <param name="effectNumber">該当効果音の番号</param>
	/// <param name="volume">該当曲の音量(0～1の間)(省略可)</param>
	int EffectLoad(SoundEffect effectNumber, float volume = 1.0f);

	/// <summary>
	/// 該当効果音を再生する
	/// </summary>
	/// <param name="effectNumber">該当効果音の番号</param>
	void EffectPlay(SoundEffect effectNumber);

	/// <summary>
	/// 該当効果音を停止する
	/// </summary>
	/// <param name="effectNumber">該当効果音の番号</param>
	void EffectStop(SoundEffect effectNumber);

	/// <summary>
	/// 該当効果音がなり終わったかどうかを調べる関数
	/// </summary>
	/// <param name="effectNumber">該当効果音の番号</param>
	/// <param name="effectContents">該当効果音の中身の番号</param>
	void EffectEnd(SoundEffect effectNumber,int effectContents);

	/// <summary>
	/// 該当効果音が再生中かどうかを取得
	/// </summary>
	/// <param name="effectNumber">該当効果音の番号</param>
	/// <returns>再生中はTrue</returns>
	bool GetEffectFlg(SoundEffect effectNumber) { return effect[(int)effectNumber].isPlay; }

	/// <summary>
	/// すべての効果音の再生情報をfalseにする
	/// </summary>
	void SetEffectALLFalse()
	{
		for (int i = 0; i < (int)SoundEffect::MaxEffect; i++)
		{
			if (GetEffectFlg((SoundEffect)i))
			{
				EffectStop((SoundEffect)i);
			}
		}
	}

	/// <summary>
	/// 該当効果音の再生情報をFalseにする
	/// </summary>
	/// <param name="effectNumber">該当効果音の番号</param>
	void SetEffectFalse(SoundEffect effectNumber)
	{
		if (effect[(int)effectNumber].isPlay == false)
		{
			return;
		}
		effect[(int)effectNumber].isPlay = false;
	}

private:

	

	struct SoundState
	{
		SoundTrack soundTrack;	// サウンド
		std::string fileName;	// ファイル名
		bool isPlay;			// 再生されているかどうか
	};
	SoundState track[(int)SoundTrack::MaxTrack];

	struct EffectState
	{
		SoundEffect soundEffect;	// 効果音
		std::string fileName;		// ファイル名
		bool isPlay;				// 再生されているかどうか
	};
	EffectState effect[(int)SoundEffect::MaxEffect];
};


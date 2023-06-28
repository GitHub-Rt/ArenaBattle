#include "GameSound.h"
#include "../Engine/Audio.h"

GameSound::GameSound()
{
	// ゲーム内音楽
	for (int i = 0; i < (int)SoundTrack::MaxTrack; i++)
	{
		track[i].soundTrack = (SoundTrack) -1;

		switch (i)
		{
			// ゲーム内音楽は、フリーBGM・音楽素材MusMus ( https://musmus.main.jp/music_game.html　)     様
			//				   魔王魂 ( https ://maou.audio/category/game/game-battle/#google_vignette ) 様
			//　　　　　　　　 DOVA-SYNDROME　( https://dova-s.jp/EN/ )　								 様   より使用しています。
			// 詳しい使用曲等は "Assets/Audio/Sound.txt"内の<ゲーム内音楽>に記載してあります。

		case (int)SoundTrack::TitleSound:
			track[i].fileName = "Audio/MusMus-BGM-157.wav";
			break;
		case (int)SoundTrack::PlaySceneSound:
			track[i].fileName = "Audio/MusMus-BGM-036.wav";
			break;
		case (int)SoundTrack::ButtleSound:
			track[i].fileName = "Audio/MusMus-BGM-069.wav";
			break;
		case (int)SoundTrack::BossSound:
			track[i].fileName = "Audio/maou_game_lastboss04.wav";
			break;
		case (int)SoundTrack::LastBossSound:
			track[i].fileName = "Audio/MusMus-BGM-039.wav";
			break;
		case (int)SoundTrack::ClearSound:
			track[i].fileName = "Audio/MusMus-JGL-027.wav";
			break;
		case (int)SoundTrack::GameOverSound:
			track[i].fileName = "Audio/MusMus-JGL-011.wav";
			break;
		case (int)SoundTrack::Alert:
			track[i].fileName = "Audio/Alert.wav";
			break;
		default:
			break;
		}

		//初期化の段階ではどれも再生されていない
		track[i].isPlay = false;
	}


	// ゲーム内効果音
	for (int i = 0; i < (int)SoundEffect::MaxEffect; i++)
	{
		effect[i].soundEffect = (SoundEffect)-1;

		switch (i)
		{
			// ゲーム内効果音は、効果音ラボ　( https://soundeffect-lab.info/ )　様より使用しています。
			// 詳しい効果音等は "Assets/Audio"内のテキストファイルに記載してあります。

		case (int)SoundEffect::Determinant:
			effect[i].fileName = "Audio/Decision.wav";
			break;
		case (int)SoundEffect::MoveSelection:
			effect[i].fileName = "Audio/MoveSelection.wav";
			break;
		case (int)SoundEffect::Touch:
			effect[i].fileName = "Audio/Invasion.wav";
			break;
		case (int)SoundEffect::GaugeRecovery:
			effect[i].fileName = "Audio/Recover.wav";
			break;
		case (int)SoundEffect::NormalAttack:
			effect[i].fileName = "Audio/NormalAttack.wav";
			break;
		case (int)SoundEffect::HardAttack:
			effect[i].fileName = "Audio/HardAttack.wav";
			break;
		case (int)SoundEffect::Damage:
			effect[i].fileName = "Audio/Damage.wav";
			break;
		default:
			break;
		}

		//初期化の段階ではどれも再生されていない
		effect[i].isPlay = false;
	}
}

void GameSound::Release()
{
}

void GameSound::SoundLoad(SoundTrack trackNumber, float volume)
{
	int hSound = Audio::Load(track[(int)trackNumber].fileName, true, volume);
	track[(int)trackNumber].soundTrack = (SoundTrack)hSound;
}

int GameSound::IntSoundLoad(SoundTrack trackNumber, bool isRoop, float volume)
{
	int hSound = Audio::Load(track[(int)trackNumber].fileName, isRoop, volume);
	track[(int)trackNumber].soundTrack = (SoundTrack)hSound;
	return hSound;
}

void GameSound::SoundPlay(SoundTrack trackNumber)
{
	if (track[(int)trackNumber].isPlay)
	{//既に再生されていたら戻る
		return;
	}
	else
	{
		track[(int)trackNumber].isPlay = true;
	}
	Audio::Play((int)track[(int)trackNumber].soundTrack);
}

void GameSound::SoundStop(SoundTrack trackNumber)
{
	if (track[(int)trackNumber].isPlay)
	{
		track[(int)trackNumber].isPlay = false;
	}
	else
	{//既に停止されていたら戻る
		return;
	}
	Audio::Stop((int)track[(int)trackNumber].soundTrack);
}

void GameSound::SoundEnd(SoundTrack trackNumber, int trackContents)
{
	if (track[(int)trackNumber].isPlay)
	{
		if (Audio::IsEndPlayBack(trackContents))
		{
			track[(int)trackNumber].isPlay = false;
		}
	}
	else
	{//既に停止されていたら戻る
		return;
	}
}

int GameSound::EffectLoad(SoundEffect effectNumber, float volume)
{
	int hSound = Audio::Load(effect[(int)effectNumber].fileName, false, volume, 20);
	effect[(int)effectNumber].soundEffect = (SoundEffect)hSound;
	return hSound;
}

void GameSound::EffectPlay(SoundEffect effectNumber)
{
	if (effect[(int)effectNumber].isPlay)
	{//既に再生されていたら戻る
		return;
	}
	else
	{
		effect[(int)effectNumber].isPlay = true;
	}
	Audio::Play((int)effect[(int)effectNumber].soundEffect);
}

void GameSound::EffectStop(SoundEffect effectNumber)
{
	if (effect[(int)effectNumber].isPlay)
	{
		effect[(int)effectNumber].isPlay = false;
	}
	else
	{//既に停止されていたら戻る
		return;
	}
	Audio::Stop((int)effect[(int)effectNumber].soundEffect);
}

void GameSound::EffectEnd(SoundEffect effectNumber, int effectContents)
{
	if (effect[(int)effectNumber].isPlay)
	{
		if (Audio::IsEndPlayBack(effectContents))
		{
			effect[(int)effectNumber].isPlay = false;
		}
	}
	else
	{//既に停止されていたら戻る
		return;
	}
}
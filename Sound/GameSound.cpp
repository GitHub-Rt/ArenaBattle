#include "GameSound.h"
#include "../Engine/Audio.h"

GameSound::GameSound()
{
	// �Q�[�������y
	for (int i = 0; i < (int)SoundTrack::MaxTrack; i++)
	{
		track[i].soundTrack = (SoundTrack) -1;

		switch (i)
		{
			// �Q�[�������y�́A�t���[BGM�E���y�f��MusMus ( https://musmus.main.jp/music_game.html�@)     �l
			//				   ������ ( https ://maou.audio/category/game/game-battle/#google_vignette ) �l
			//�@�@�@�@�@�@�@�@ DOVA-SYNDROME�@( https://dova-s.jp/EN/ )�@								 �l   ���g�p���Ă��܂��B
			// �ڂ����g�p�ȓ��� "Assets/Audio/Sound.txt"����<�Q�[�������y>�ɋL�ڂ��Ă���܂��B

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

		//�������̒i�K�ł͂ǂ���Đ�����Ă��Ȃ�
		track[i].isPlay = false;
	}


	// �Q�[�������ʉ�
	for (int i = 0; i < (int)SoundEffect::MaxEffect; i++)
	{
		effect[i].soundEffect = (SoundEffect)-1;

		switch (i)
		{
			// �Q�[�������ʉ��́A���ʉ����{�@( https://soundeffect-lab.info/ )�@�l���g�p���Ă��܂��B
			// �ڂ������ʉ����� "Assets/Audio"���̃e�L�X�g�t�@�C���ɋL�ڂ��Ă���܂��B

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

		//�������̒i�K�ł͂ǂ���Đ�����Ă��Ȃ�
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
	{//���ɍĐ�����Ă�����߂�
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
	{//���ɒ�~����Ă�����߂�
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
	{//���ɒ�~����Ă�����߂�
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
	{//���ɍĐ�����Ă�����߂�
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
	{//���ɒ�~����Ă�����߂�
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
	{//���ɒ�~����Ă�����߂�
		return;
	}
}
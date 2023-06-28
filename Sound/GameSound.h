#pragma once
#include <string>

// �Q�[�������y
enum class SoundTrack
{
	TitleSound = 0,	// �^�C�g���V�[�����̉��y
	PlaySceneSound,		// �v���C�V�[���̉��y
	ButtleSound,	// �m�[�}���G�Ƃ̐퓬���y
	BossSound,		// �{�X��̐퓬���y
	LastBossSound,	// ��2�`�Ԃ̃{�X��̐퓬���y
	ClearSound,		// �N���A���̉��y
	GameOverSound,	// �Q�[���I�[�o�[�̉��y
	Alert,				// �{�X�o�ꉉ�o�����ʉ�
	MaxTrack		// �Q�[�������y�̍ő吔
};

// �Q�[�������ʉ�
enum class SoundEffect
{
	Determinant = 0,	// �I�����莞���ʉ�
	MoveSelection,		// �I�����ڈړ������ʉ�
	Touch,				// PlayScene���̉��F�����ɐG�ꂽ���̌��ʉ�
	GaugeRecovery,		// �̗̓Q�[�W�񕜎����ʉ�
	NormalAttack,		// �ʏ�U�������ʉ�
	HardAttack,			// ���U�������ʉ�
	Damage,				// ��_���[�W�����ʉ�
	MaxEffect			// ���ʉ��̍ő吔
};


class GameSound
{
public:
	GameSound();

	void Release();

	/// <summary>
	/// �T�E���h�S�̂̍Đ�����false�ɂ���֐�
	/// </summary>
	void SetALLFalse()
	{
		SetSoundALLFalse();
		SetEffectALLFalse();
	}




	/////////      �Q�[�������y�̊֐�      //////////////



	/// <summary>
	/// �Y���Ȃ����[�h����(�������[�v)
	/// </summary>
	/// <param name="trackNumber">�Y���Ȃ̔ԍ�</param>
	/// <param name="volume">�Y���Ȃ̉���(0�`1�̊�)(�ȗ���)</param>
	void SoundLoad(SoundTrack trackNumber, float volume = 1.0f);
	
	/// <summary>
	/// �Y���Ȃ����[�h����(�Đ������I��)
	/// </summary>
	/// <param name="trackNumber">�Y���Ȃ̔ԍ�</param>
	/// <param name="isRoop">true���������[�v�Afalse���P�x�̂�</param>
	/// <param name="volume">�Y���Ȃ̉���(0�`1�̊�)(�ȗ���)</param>
	int IntSoundLoad(SoundTrack trackNumber, bool isRoop, float volume = 1.0f);

	/// <summary>
	/// �Y���Ȃ̍Đ����s��
	/// </summary>
	/// <param name="track">�Y���Ȃ̔ԍ�</param>
	void SoundPlay(SoundTrack trackNumber);
	
	/// <summary>
	/// �Y���Ȃ��~����
	/// </summary>
	/// <param name="track">�Y���Ȃ̔ԍ�</param>
	void SoundStop(SoundTrack trackNumber);

	/// <summary>
	/// �Y���Ȃ��P���������ǂ����𒲂ׂ�
	/// </summary>
	/// <param name="trackNumber">�Y���Ȃ̔ԍ�</param>
	/// <param name="trackContents">�Y���Ȃ̒��g�̔ԍ�</param>
	void SoundEnd(SoundTrack trackNumber, int trackContents);

	/// <summary>
	/// �Y���Ȃ��Đ������ǂ������擾
	/// </summary>
	/// <param name="trackNumber">�Y���Ȃ̔ԍ�</param>
	/// <returns>�Đ�����True</returns>
	bool GetSoundFlg(SoundTrack trackNumber) { return track[(int)trackNumber].isPlay; }

	/// <summary>
	/// ���ׂĂ̋Ȃ̍Đ�����false�ɂ���
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
	/// �Y���Ȃ̍Đ�����False�ɂ���
	/// </summary>
	/// <param name="trackNumber">�Y���Ȃ̔ԍ�</param>
	void SetSoundFalse(SoundTrack trackNumber)
	{
		if (track[(int)trackNumber].isPlay == false)
		{
			return;
		}
		track[(int)trackNumber].isPlay = false;
	}





	///////     �Q�[�������ʉ��̊֐�    //////////

	/// <summary>
	/// �Y�����ʉ������[�h����
	/// </summary>
	/// <param name="effectNumber">�Y�����ʉ��̔ԍ�</param>
	/// <param name="volume">�Y���Ȃ̉���(0�`1�̊�)(�ȗ���)</param>
	int EffectLoad(SoundEffect effectNumber, float volume = 1.0f);

	/// <summary>
	/// �Y�����ʉ����Đ�����
	/// </summary>
	/// <param name="effectNumber">�Y�����ʉ��̔ԍ�</param>
	void EffectPlay(SoundEffect effectNumber);

	/// <summary>
	/// �Y�����ʉ����~����
	/// </summary>
	/// <param name="effectNumber">�Y�����ʉ��̔ԍ�</param>
	void EffectStop(SoundEffect effectNumber);

	/// <summary>
	/// �Y�����ʉ����Ȃ�I��������ǂ����𒲂ׂ�֐�
	/// </summary>
	/// <param name="effectNumber">�Y�����ʉ��̔ԍ�</param>
	/// <param name="effectContents">�Y�����ʉ��̒��g�̔ԍ�</param>
	void EffectEnd(SoundEffect effectNumber,int effectContents);

	/// <summary>
	/// �Y�����ʉ����Đ������ǂ������擾
	/// </summary>
	/// <param name="effectNumber">�Y�����ʉ��̔ԍ�</param>
	/// <returns>�Đ�����True</returns>
	bool GetEffectFlg(SoundEffect effectNumber) { return effect[(int)effectNumber].isPlay; }

	/// <summary>
	/// ���ׂĂ̌��ʉ��̍Đ�����false�ɂ���
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
	/// �Y�����ʉ��̍Đ�����False�ɂ���
	/// </summary>
	/// <param name="effectNumber">�Y�����ʉ��̔ԍ�</param>
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
		SoundTrack soundTrack;	// �T�E���h
		std::string fileName;	// �t�@�C����
		bool isPlay;			// �Đ�����Ă��邩�ǂ���
	};
	SoundState track[(int)SoundTrack::MaxTrack];

	struct EffectState
	{
		SoundEffect soundEffect;	// ���ʉ�
		std::string fileName;		// �t�@�C����
		bool isPlay;				// �Đ�����Ă��邩�ǂ���
	};
	EffectState effect[(int)SoundEffect::MaxEffect];
};


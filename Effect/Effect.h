#pragma once

#include "../Engine/VFX.h"

enum class EmitterType
{
	Detonation = 0,	//���j�G�t�F�N�g
	Ventilation,	//���؂�G�t�F�N�g
	Tornado,		//�����G�t�F�N�g
	MaxEmmierType
};


class Effect
{

public:

	Effect();
	void Release();



	//���j�G�t�F�N�g�Ɋւ���֐�

	/// <summary>
	/// �����G�t�F�N�g���o���֐�
	/// </summary>
	void StartEffectDetonation();

	/// <summary>
	/// ���j�G�t�F�N�g���~����֐�
	/// </summary>
	void StopEffectDetonation();




	// ���U���G�t�F�N�g�Ɋւ���֐�

	/// <summary>
	/// ���U���G�t�F�N�g���J�n����֐�
	/// </summary>
	void StartEffectAtHardAttack();

	/// <summary>
	/// ���U���G�t�F�N�g���~����֐�
	/// </summary>
	void StopEffectAtHardAttack();




	// �ʏ�U���G�t�F�N�g����

	/// <summary>
	/// �ʏ�U���G�t�F�N�g���J�n����֐�
	/// </summary>
	void StartEffectAtNormalAttack();

	/// <summary>
	/// �ʏ�U���G�t�F�N�g���~����֐�
	/// </summary>
	void StopEffectAtNormalAttack();
	

	/// <summary>
	/// �G�t�F�N�g�̕\���ʒu���Z�b�g����֐�
	/// </summary>
	/// <param name="pos">�G�~�b�^�[�ʒu</param>
	/// /// <param name="type">�G�t�F�N�g���</param>
	void SetEmitterPosition(XMFLOAT3 pos, EmitterType type);



	void SetDirection(XMFLOAT3 dir, XMFLOAT3 rotate) 
	{
		XMVECTOR vec = XMLoadFloat3(&dir);
		XMVECTOR vInverse = -vec;
		
		XMStoreFloat3(&ventilationDir, vec);
		ventilationDir.z -= 0.25f;
		ventilationRotate = rotate;
	}

private:

	//���j�G�t�F�N�g���̕ϐ�
	EmitterData data_Detonation;
	int eLimitFire;
	int eLimitSparks;
	int eLimitGround;

	//�����G�t�F�N�g���̕ϐ�
	EmitterData data_Tornado;
	int eLimitTornado;

	//���؂�G�t�F�N�g���̕ϐ�
	XMFLOAT3 ventilationDir;
	XMFLOAT3 ventilationRotate;
	EmitterData data_Ventilation;
	int eLimitVentilation;
};


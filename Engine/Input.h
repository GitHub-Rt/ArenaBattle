#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dInput.h>
#include <DirectXMath.h>
#include <list>
#include "XInput.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")
#pragma comment(lib, "Xinput.lib")


using namespace DirectX;

enum class MouseBottunCode
{
	LeftClick,
	RightClick,
	CenterClick
};

//-----------------------------------------------------------
//DirectInput���g�����L�[�{�[�h���͏���
//-----------------------------------------------------------
namespace Input
{
	//������
	//�����FhWnd	�E�B���h�E�n���h��
	void Initialize(HWND hWnd);

	//�X�V
	void Update();


	///////////////////////////�@�L�[�{�[�h�@//////////////////////////////////
	//�L�[��������Ă��邩���ׂ�
	//�����FkeyCode	���ׂ����L�[�̃R�[�h
	//�ߒl�F������Ă����true
	bool IsKey(int keyCode);

	//�L�[���������������ׂ�i�������ςȂ��͖����j
	//�����FkeyCode	���ׂ����L�[�̃R�[�h
	//�ߒl�F�������u�Ԃ�������true
	bool IsKeyDown(int keyCode);

	//�L�[���������������ׂ�
	//�����FkeyCode	���ׂ����L�[�̃R�[�h
	//�ߒl�F�������u�Ԃ�������true
	bool IsKeyUp(int keyCode);

	///////////////////////////�@�}�E�X�@//////////////////////////////////
	//�}�E�X�̃{�^����������Ă��邩���ׂ�
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F������Ă����true
	bool IsMouseButton(MouseBottunCode buttonCode);

	//�}�E�X�̃{�^�����������������ׂ�i�������ςȂ��͖����j
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F�������u�Ԃ�������true
	bool IsMouseButtonDown(MouseBottunCode buttonCode);

	//�}�E�X�̃{�^�����������������ׂ�
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F�������u�Ԃ�������true
	bool IsMouseButtonUp(MouseBottunCode buttonCode);


	//�}�E�X�J�[�\���̈ʒu���擾
	//�ߒl�F�}�E�X�J�[�\���̈ʒu
	XMFLOAT3 GetMousePosition();

	//�}�E�X�J�[�\���̈ʒu���Z�b�g
	//�����F�}�E�X�J�[�\���̈ʒu
	void SetMousePosition(int x, int y);

	//���̃t���[���ł̃}�E�X�̈ړ��ʂ��擾
	//�ߒl�FX,Y �}�E�X�̈ړ��ʁ@�^�@Z,�z�C�[���̉�]��
	XMFLOAT3 GetMouseMove();

	/// <summary>
	/// �}�E�X�J�[�\���ʒu�̃Z�b�g
	/// </summary>
	/// <param name="x">�}�E�X�J�[�\����x���W</param>
	/// <param name="y">�}�E�X�J�[�\����y���W</param>
	void SetMouseMove(int x, int y);

	/// <summary>
	/// �}�E�X�̃��[�h��ύX����֐�
	/// </summary>
	void ChangeModeFlg();

	/// <summary>
	/// �}�E�X�̃��[�h���擾����֐�
	/// </summary>
	/// <returns>�f�o�b�O���[�h�Ȃ�true</returns>
	bool GetMouseFlg();


	///////////////////////////�@�R���g���[���[�@//////////////////////////////////
	//�R���g���[���[�̃{�^����������Ă��邩���ׂ�
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F������Ă����true
	bool IsPadButton(int buttonCode, int padID = 0);

	//�R���g���[���[�̃{�^�����������������ׂ�i�������ςȂ��͖����j
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F�������u�Ԃ�������true
	bool IsPadButtonDown(int buttonCode, int padID = 0);

	//�R���g���[���[�̃{�^�����������������ׂ�
	//�����FbuttonCode	���ׂ����{�^���̔ԍ�
	//�ߒl�F�������u�Ԃ�������true
	bool IsPadButtonUp(int buttonCode, int padID = 0);

	//���X�e�B�b�N�̌X�����擾
	//�ߒl:�X����i-1�`1�j
	XMFLOAT3 GetPadStickL(int padID = 0);

	//�E�X�e�B�b�N�̌X�����擾
	//�ߒl:�X����i-1�`1�j
	XMFLOAT3 GetPadStickR(int padID = 0);

	//���g���K�[�̉������݋���擾
	//�ߒl:�������݋�i0�`1�j
	float		GetPadTrrigerL(int padID = 0);

	//�E�g���K�[�̉������݋���擾
	//�ߒl:�������݋�i0�`1�j
	float		GetPadTrrigerR(int padID = 0);

	//�U��������
	void SetPadVibration(int l, int r, int padID = 0);




	//�J��
	void Release();


};

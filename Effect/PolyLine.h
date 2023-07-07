#pragma once
#include <list>
#include "../Engine/Direct3D.h"
#include "../Engine/Texture.h"
#include <DirectXMath.h>
#include <string>
using namespace DirectX;
using namespace std;


//�R���X�^���g�o�b�t�@�[
struct CONSTANT_BUFFER_POLY
{
	XMMATRIX	matWVP;
	XMFLOAT4	color;
};

//���_���
struct VERTEX_POLY
{
	XMFLOAT3 position;
	XMFLOAT3 uv;
};


class PolyLine
{
public:
	//�R���X�g���N�^
	PolyLine();

	//���݂̈ʒu���L��������
	//�����Fpos	���݂̈ʒu
	void AddPosition(XMFLOAT3 pos);

	//���[�h
	//�����FfileName	�摜�t�@�C����
	//�ߒl�F����/���s
	HRESULT Load(std::string fileName);

	//�`��
	void Draw();

	//���
	void Release();

private:

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;	//�摜


	list<XMFLOAT3> positions_;	//�ߋ�length_�񕪂̈ʒu
};

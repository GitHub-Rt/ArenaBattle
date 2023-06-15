#pragma once
#include <list>
#include "../Engine/Direct3D.h"
#include "../Engine/Texture.h"
#include <DirectXMath.h>
#include <string>
using namespace DirectX;
using namespace std;


//コンスタントバッファー
struct CONSTANT_BUFFER_POLY
{
	XMMATRIX	matWVP;
	XMFLOAT4	color;
};

//頂点情報
struct VERTEX_POLY
{
	XMFLOAT3 position;
	XMFLOAT3 uv;
};


class PolyLine
{
public:
	//コンストラクタ
	PolyLine();

	//現在の位置を記憶させる
	//引数：pos	現在の位置
	void AddPosition(XMFLOAT3 pos);

	//ロード
	//引数：fileName	画像ファイル名
	//戻値：成功/失敗
	HRESULT Load(std::string fileName);

	//描画
	void Draw();

	//解放
	void Release();

private:

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	Texture* pTexture_;	//画像


	list<XMFLOAT3> positions_;	//過去length_回分の位置
};


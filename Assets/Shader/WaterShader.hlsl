
//    register ----v　引き出しみたいなもの
Texture2D tex : register(t0);		//テクスチャーを受け取る
SamplerState smp : register(s0);	//サンプルを受け取る
Texture2D texNormal:register(t1);	//Normalテクスチャーを受け取る


cbuffer global
{
	float4x4 matW;			//ワールド行列
	float4x4 matWVP;		//ワールド・ビュー・プロダクションの合成行列
	float4x4 matNormal;		//法線変形させるための行列
	float4  camPos;			//カメラの位置
	float4	 color;			//マテリアルの色
	float4 ambient;			//環境光
	float4 specular;		//ハイライトの色
	float	shiness;		//ハイライトの強さ
	bool	 isTexture;		//テクスチャの有無
	float scroll;			//uvスクロール
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
	float4 color : TEXCOORD1;
	float4 specular : TEXCOORD2;
	float4 V : TEXCOORD3;
	float4 R : TEXCOORD4;
	float4 light : TEXCOORD5;
	float4 normal : TEXCOORD6;
};


//頂点シェーダー
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL, float4 tangent : TANGENT)
{
	//ピクセルシェーダーに渡す変数
	VS_OUT outData;


	outData.pos = mul(pos, matWVP);		//ベクトルを行列で変形させる関数 --> mul(ベクトル,行列)
	outData.uv = uv;


	//法線
	normal = mul(normal, matNormal);
	normal = normalize(normal);
	normal.w = 0;


	tangent = mul(tangent, matNormal);
	tangent = normalize(tangent);
	tangent.w = 0;

	//従法線
	float3 binormal = cross(normal, tangent);
	binormal = mul(binormal, matNormal);
	binormal = normalize(binormal);


	//視線ベクトル(頂点からカメラに向かうベクトル)
	float4 eye = normalize(camPos - mul(outData.pos, matW));
	outData.V.x = dot(eye, tangent);
	outData.V.y = dot(eye, binormal);
	outData.V.z = dot(eye, normal);
	outData.V.w = 0;


	//ライト方向
	float4 light = float4(1, 3, -1, 0);
	light = normalize(light);

	outData.light.x = dot(light, tangent);
	outData.light.y = dot(light, binormal);
	outData.light.z = dot(light, normal);
	outData.light.w = 0;

	//まとめて渡す
	return outData;
}

//ピクセルシェーダー
//（） : セマンティクス----------------v
float4 PS(VS_OUT inData) : SV_TARGET
{
	float4 diffuse;
	float4 ambient_;

	float2 uv1 = inData.uv;
	uv1.x += scroll;
	float4 normal1 = texNormal.Sample(smp, uv1) * 2 - 1;


	float2 uv2 = inData.uv;
	uv2.x -= scroll * 0.3;
	uv2.y *= 1.2f;
	float4 normal2 = texNormal.Sample(smp, uv2) * 2 - 1;

	float4 normal = normal1 + normal2;
	normal.w = 0;
	normal = normalize(normal1);


	inData.color = dot(normal, inData.light);
	inData.color = clamp(inData.color, 0, 1);



	//反射した光のベクトル   : reflect関数(ベクトル、法線)
	inData.R = reflect(inData.light, normal);

	//内積のべき乗でハイライトになる
	inData.specular = pow(clamp(dot(inData.R, inData.V), 0, 1), shiness) * specular;



	if (isTexture == true)
	{
		diffuse = tex.Sample(smp, inData.uv) * inData.color;
		ambient_ = tex.Sample(smp, inData.uv) * ambient;
	}
	else
	{
		diffuse = color * inData.color;
		ambient_ = color * ambient;
	}
	float4 result = diffuse + ambient_ + inData.specular;

	result.a = 0;

	return result;
}
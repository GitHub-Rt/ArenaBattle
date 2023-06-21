#pragma once
#include "GameObject.h"


//-----------------------------------------------------------
//一番トップに来るオブジェクト
//すべてのオブジェクトは、これの子孫になる
//-----------------------------------------------------------
class RootObject :	public GameObject
{
public:
	RootObject();
	~RootObject();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	// プレイヤーの通常カメラ関数を呼ぶ関数(シャドーマップ後のカメラセットのため)
	void PlayerCamera();
};


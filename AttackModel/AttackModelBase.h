#pragma once
#include "../Engine/GameObject.h"

enum class SCENE_ID;

class EnemyBoss;

class AttackModelBase : public GameObject
{
public:

	AttackModelBase(GameObject* parent, std::string fileName);
	~AttackModelBase();
	void Update() override;
	void Draw() override;
	void Release() override;

	void AttackModelLoad(std::string fileName);
	int AttackModelLoadInt(std::string fileName);
	void AttackModelDraw(int modelHandle);
	void AttackModelDraw(int modelHandle, Transform trans);
	void AttackModelAddBoxCollider(XMFLOAT3 size, XMFLOAT3 center = XMFLOAT3(0, 0, 0));
	void AttackModelAddSphereCollider(float radius, XMFLOAT3 center = XMFLOAT3(0, 0, 0));

	SCENE_ID GetSceneID();

	float PositionAdjustment(XMFLOAT3 pos);

	// 行動範囲外ならtrueを返す
	bool IsMoveLimit(XMFLOAT3 nextPosition);

	int GetAttackModelHandle() { return hModel; }

	virtual void AttackModelUpdate() = 0;

	/// <summary>
	/// 真下にあるオブジェクトが該当オブジェクトかどうかを返す関数
	/// </summary>
	/// <param name="position">オブジェクトの現在位置</param>
	/// <param name="position">調べたいオブジェクト</param>
	/// <returns>真下にあるオブジェクトのポインタ</returns>
	bool IsObjectUnder(XMFLOAT3 position, int handle);

private:

	int hModel;
	EnemyBoss* pBoss;
};


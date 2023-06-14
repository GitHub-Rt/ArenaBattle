#pragma once
#include "../Engine/GameObject.h"

enum class SCENE_ID;

class AttackModelBase : public GameObject
{
public:

	AttackModelBase(GameObject* parent, std::string fileName);
	~AttackModelBase();
	void Update() override;
	void Draw() override;
	void Release() override;

	void AttackModelLoad(std::string fileName);
	void AttackModelDraw(int modelHandle);
	void AttackModelAddBoxCollider(XMFLOAT3 size, XMFLOAT3 center = XMFLOAT3(0, 0, 0));
	void AttackModelAddSphereCollider(float radius, XMFLOAT3 center = XMFLOAT3(0, 0, 0));

	SCENE_ID GetSceneID();

	// çsìÆîÕàÕäOÇ»ÇÁtrueÇï‘Ç∑
	bool IsMoveLimit(XMFLOAT3 nextPosition);

	virtual void AttackModelUpdate() = 0;

private:
	int hModel;
};


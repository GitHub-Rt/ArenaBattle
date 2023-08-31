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

	// �s���͈͊O�Ȃ�true��Ԃ�
	bool IsMoveLimit(XMFLOAT3 nextPosition);

	int GetAttackModelHandle() { return hModel; }

	virtual void AttackModelUpdate() = 0;

	/// <summary>
	/// �^���ɂ���I�u�W�F�N�g���Y���I�u�W�F�N�g���ǂ�����Ԃ��֐�
	/// </summary>
	/// <param name="position">�I�u�W�F�N�g�̌��݈ʒu</param>
	/// <param name="position">���ׂ����I�u�W�F�N�g</param>
	/// <returns>�^���ɂ���I�u�W�F�N�g�̃|�C���^</returns>
	bool IsObjectUnder(XMFLOAT3 position, int handle);

private:

	int hModel;
	EnemyBoss* pBoss;
};


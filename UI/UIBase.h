#pragma once
#include "../Engine/GameObject.h"

enum class RectUI
{
	RecoveryNumber,
};

class UIBase : public GameObject
{
public:
	UIBase(GameObject* parent, std::string fileName);
	~UIBase();
	int UILoad(std::string fileName);
	void Update() override;
	void UIDraw(int handle, Transform trans);
	void Release() override;

	// �摜�̐؂蔲�����K�v�Ȏ��ɌĂԊ֐�
	void UIRect(RectUI target,int handle, int num = 0);

	// UI�̓����x
	void UIAlpha(int handle, int alpha);

	// �X�V�������K�v��UI�̂݌Ă΂��
	virtual void UIUpdate() {}
};


#pragma once
#include "UIBase.h"

class Warning : public UIBase
{
public:
	Warning(GameObject* parent);
	~Warning();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;

	// �����x��ύX����֐�
	void ChangeAlpha();

private:
	int hPict;          //�e�L�X�g�摜
	int hPictBack;      //�w�i�摜
	int alphaTimer;     //�����x���Ǘ�����^�C�}�[
	int keepTimer;      //��Ԃ����������鎞�Ԍv���^�C�}�[
	bool isGain;        //�����x���オ���Ă��邩�ǂ���
	float alpha;        //�e�L�X�g�����x
};


#pragma once
#include "UIBase.h"

class SelectBox : public UIBase
{
public:

	SelectBox(GameObject* parent);
	~SelectBox();
	void Initialize() override;
	void UIUpdate() override;
	void Draw() override;
		
	/// <summary>
	/// �Z���N�g�{�b�N�X�̃|�W�V�������Z�b�g����֐�
	/// </summary>
	/// <param name="pos">�|�W�V����</param>
	/// <param name="isScaleXChange">x���g�傷�邩�ǂ���</param>
	void SetSelectBox(XMFLOAT3 pos, bool isScaleXChange = false);

private:

	int hPict;
};


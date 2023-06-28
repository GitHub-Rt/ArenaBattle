#pragma once
#include "../Engine/GameObject.h"

// �g�p����摜�̎��
enum class FramePict
{
	PICT_FRAME = 0,
	PICT_GREEN,
	PICT_LGREEN,
	PICT_RED,
	PICT_MAX
};

//�萔�錾
const float DMG_SPEED = 0.0025f;      //�_���[�W�o�[�̑��x
const float RCV_SPEED = 0.005f;       //�񕜃o�[�̑��x

class HPGaugeBase : public GameObject
{
public:
	HPGaugeBase(GameObject* parent, std::string fileName);
	~HPGaugeBase();
	void Update() override;
	void GaugeImageDraw(int pictHandle, Transform trans);
	void Release() override;

	void Damage(float value);
	void Recovery(float value);

	int GaugeImageLoad(std::string fileName);

	void SetGaugePosition(float x, float y)
	{
		transform_.position_.x = x;
		transform_.position_.y = y;
	}
	void SetGaugeScale(XMFLOAT3 scale) { transform_.scale_ = scale; }
	void SetMaxHP(float maxValue) { MAX_HP = maxValue; }

	void SetGaugeInformation();

	float GetStopRatio() { return stopRatio; }
	float GetMoveRatio() { return moveRatio; }

private:

	float MAX_HP;

	float nowHp;	// ���݂̗̑�
	float maxHp;	// �ő�̗�

	float stopRatio;	// �ő�HP�ɑ΂���Œ肳�ꂽ�Q�[�W�̊���
	float moveRatio;	// �ő�HP�ɑ΂���ω����Ă�Q�[�W�̊���

};


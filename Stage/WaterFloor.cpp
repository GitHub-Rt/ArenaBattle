#include "WaterFloor.h"
#include "../Engine/Direct3D.h"

WaterFloor::WaterFloor(GameObject* parent)
	: StageBase(parent, "WaterFloor")
{

}

WaterFloor::~WaterFloor()
{

}

void WaterFloor::Initialize()
{
	StageModelLoad("water.fbx");

	transform_.scale_.x = 150;
	transform_.scale_.z = 150;

	transform_.position_.y -= 12;
}

void WaterFloor::Draw()
{
	// ��p�̃V�F�[�_�[�ɕύX����
	Direct3D::SetShader(Direct3D::SHADER_WATER);
	StageDraw(transform_);

	// ���̃V�F�[�_�[�ɖ߂�
	Direct3D::SetShader(Direct3D::SHADER_3D);
}
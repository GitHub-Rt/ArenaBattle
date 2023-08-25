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
	// 専用のシェーダーに変更する
	Direct3D::SetShader(Direct3D::SHADER_WATER);
	StageDraw(transform_);

	// 元のシェーダーに戻す
	Direct3D::SetShader(Direct3D::SHADER_3D);
}
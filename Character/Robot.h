#pragma once
#include "CharacterBase.h"

class Player;

// 内部データを格納しているCSVファイルの該当項目に対応した行数を管理する
enum class RobotData
{
	BulletTimer = 1
};

// ロボットを管理するクラス
class Robot : public CharacterBase
{
public:

	float GetAttackValue() { return GetParameterValue(CharacterID::Robot, CharacterStatus::AttackPower); }


	void SetData() override;
	Robot(GameObject* parent);
	~Robot();
	void Initialize()  override;
	void Release() override;
	void CharacterUpdate() override;
	void CharacterIdleAction() override;
	void CharacterMove() override;
	void CharacterAttack() override;

	void CharacterCheckHP() override {};
	void CharacterJumpAction()override {};
	void CharacterDodingAction()override {};
	void CharacterStunAction() override {};
	void CharacterTakeDamage(float damage) override {};
	void DrawEffect() override {};

	//　プレイヤーのカメラ奥方向にモデルを回転させる(弾の打つ方向を決める)
	void SetAngle();

private:
	
	// InternalDataCSVから値を格納する変数
	int BETWEEN_BULLETTIMER;			// 弾が発射する間隔

	Player* pPlayer;
	int bulletTimer;
};


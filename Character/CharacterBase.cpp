#include "CharacterBase.h"
#include "../Engine/BoxCollider.h"
#include "../Engine/Camera.h"

#include "../Scene/SceneManager.h"
#include "../Stage/StageBase.h"

//定数宣言

const XMFLOAT3 RAY_DIRECTION = { 0,-1,0 };	// レイの方向

// ParameterCSVの各データの番号
const int MAX_HP = 1;
const int ATTACK = 2;
const int DEFENCE = 3;
const int PLAYER_PARAMTER = 1;
const int ROBOT_PARAMTER = 2;
const int NORMALENEMY_PARAMTER = 3;
const int BOSSENEMY_PARAMTER = 4;


// InternalDataCSVの番号
const int INTERNALDATA = 1;


CharacterBase::CharacterBase(GameObject* parent, std::string fileName)
	:GameObject(parent, fileName)
{
	hModel = -1;
	groundHundle = -1;
	value = -1;
	internalData = -1;
	calCount = 0;
	damage = 0;

	//外部データファイルのロード
	ParameterCSV.Load("Character/Data/characterParameter.csv");
	PlayerInternalDataCSV.Load("Character/Data/PlayerInternalData.csv");
	RobotInternalDataCSV.Load("Character/Data/RobotInternalData.csv");
	EnemyInternalDataCSV.Load("Character/Data/EnemyInternalData.csv");
	EnemyBossInternalDataCSV.Load("Character/Data/EnemyBossInternalData.csv");

	parameter.hp = 0;
	parameter.attack = 0;
	parameter.defense = 0;

	ChangeState(CharacterState::Idle);
	attackStage = AttackStage::NoAttack;
	damageStage = DamageStage::NoDamage;
}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::Update()
{
	if (IsEntered())
	{
		CharacterUpdate();

		for (unsigned int nowState = (unsigned int)CharacterState::Idle; nowState <= (unsigned int)CharacterState::MAX_CharacterState; nowState++)
		{
			CharacterState nowAction = (CharacterState)nowState;

			// 状態フラグが立っているかどうかをチェックする
			if (IsStateSet(nowAction))
			{
				switch (nowAction)
				{
				case CharacterState::Idle:
					CharacterIdleAction();
					break;
				case CharacterState::Moving:
					CharacterMove();
					break;
				case CharacterState::Attacking:
					CharacterAttack();
					break;
				case CharacterState::Damaged:
					CharacterTakeDamage(damage);
					break;
				case CharacterState::Dodging:
					CharacterDodingAction();
					break;
				case CharacterState::Jumping:
					CharacterJumpAction();
					break;
				case CharacterState::Stan:
					CharacterStunAction();
					break;
				default:
					break;
				}
			}
		}

		
		
	}
	
}

void CharacterBase::Draw()
{
	CharacterDraw(hModel);
	

	DrawEffect();
}

void CharacterBase::CharacterModelLoad(std::string fileName)
{
	hModel = Model::Load("Character/Model/" + fileName);
	assert(hModel >= 0);
}

void CharacterBase::CharacterAddCollider(XMFLOAT3 size, XMFLOAT3 center)
{
	BoxCollider* myCollision = new BoxCollider(center, size);
	AddCollider(myCollision);
}

void CharacterBase::ColorChange(float red, float green, float blue, float alpha)
{
	Model::ChangeColor(hModel, red, green, blue, alpha);
}

void CharacterBase::RestoreOriginalColor()
{
	Model::RestoreOriginalColor(hModel);
}

void CharacterBase::ChangeDamageColor(bool isDamage)
{
	Model::SetDamageColor(hModel, isDamage);
}

void CharacterBase::CharacterDraw(int charaModel)
{
	hModel = charaModel;
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void CharacterBase::CharacterDamageCalculation(CharacterID attackChara, CharacterID target, int indexNumber, float magnification)
{
	// 攻撃を行ったキャラと受けたキャラのパラメータを取得してくる
	Parameters attackParameter = GetParameter(attackChara);
	Parameters targetParameter = GetParameter(target);

	// ダメージ量の計算
	float attackDamage = attackParameter.attack * magnification - targetParameter.defense;

	
	SetTakeDamageStart(target, attackDamage, indexNumber);
	
}

void CharacterBase::SetTakeDamageStart(CharacterID target, float attackDamage, int indexNumber)
{
	CharacterBase* pTarget = nullptr;

	switch (target)
	{
	case CharacterID::Player:
		pTarget = (CharacterBase*)FindObject("Player");
		break;
	case CharacterID::Robot:
		pTarget = (CharacterBase*)FindObject("Robot");
		break;
	case CharacterID::NormalEnemy:
		pTarget = (CharacterBase*)EnemyManager::GetEnemyContent(indexNumber);
		break;
	case CharacterID::EnemyBoss:
		pTarget = (CharacterBase*)FindObject("EnemyBoss");
		break;
	default:
		break;
	}

	pTarget->SetDamage(attackDamage);
}

XMVECTOR CharacterBase::GetFrontVector()
{
	XMVECTOR vFront = { 0,0,1,0 };
	XMMATRIX mAngle = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	vFront = XMVector3TransformCoord(vFront, mAngle);
	XMVector3Normalize(vFront);

	return vFront;
}

float CharacterBase::PositionAdjustment(XMFLOAT3 position)
{
	const float START_PLUS_Y = 100;	// 高い位置からレイを発射させるため

	SceneManager* pManager = (SceneManager*)FindObject("SceneManager");
	SCENE_ID nowScene = pManager->GetSceneID();
	StageBase* pStage = nullptr;

	switch (nowScene)
	{
	case SCENE_ID::SCENE_ID_BATTLE:
	case SCENE_ID::SCENE_ID_DEBUG:
		pStage = (StageBase*)FindObject("Stage");
		break;
	case SCENE_ID::SCENE_ID_PLAY:
		pStage = (StageBase*)FindObject("NormalField");
		break;
	default:
		break;
	}

	if (pStage != nullptr)
	{
		groundHundle = pStage->GetModelHandle();


		RayCastData data;
		data.start = position;
		data.start.y += START_PLUS_Y;
		data.dir = RAY_DIRECTION;
		Model::RayCast(groundHundle, &data);

		if (data.hit)
		{
			// 高くした値を取り除いて返す
			return data.dist - START_PLUS_Y;
		}
	}
}

void CharacterBase::SetParameter(CharacterID id)
{
	switch (id)
	{
	case CharacterID::Player:
		SetParameter(
			parameter.hp = ParameterCSV.GetValue(MAX_HP, PLAYER_PARAMTER),
			parameter.attack = ParameterCSV.GetValue(ATTACK, PLAYER_PARAMTER),
			parameter.defense = ParameterCSV.GetValue(DEFENCE, PLAYER_PARAMTER));
		break;
	case CharacterID::Robot:
		SetParameter(
			parameter.hp = ParameterCSV.GetValue(MAX_HP, ROBOT_PARAMTER),
			parameter.attack = ParameterCSV.GetValue(ATTACK, ROBOT_PARAMTER),
			parameter.defense = ParameterCSV.GetValue(DEFENCE, ROBOT_PARAMTER));
		break;
	case CharacterID::NormalEnemy:
		SetParameter(
			parameter.hp = ParameterCSV.GetValue(MAX_HP, NORMALENEMY_PARAMTER),
			parameter.attack = ParameterCSV.GetValue(ATTACK, NORMALENEMY_PARAMTER),
			parameter.defense = ParameterCSV.GetValue(DEFENCE, NORMALENEMY_PARAMTER));
		break;
	case CharacterID::EnemyBoss:
		SetParameter(
			parameter.hp = ParameterCSV.GetValue(MAX_HP, BOSSENEMY_PARAMTER),
			parameter.attack = ParameterCSV.GetValue(ATTACK, BOSSENEMY_PARAMTER),
			parameter.defense = ParameterCSV.GetValue(DEFENCE, BOSSENEMY_PARAMTER));
		break;
	default:

		break;
	}
}

Parameters CharacterBase::GetParameter(CharacterID id)
{
	Parameters data = { 0,0,0 };

	switch (id)
	{
	case CharacterID::Player:
		SetParameter(
			data.hp = ParameterCSV.GetValue(MAX_HP, PLAYER_PARAMTER),
			data.attack = ParameterCSV.GetValue(ATTACK, PLAYER_PARAMTER),
			data.defense = ParameterCSV.GetValue(DEFENCE, PLAYER_PARAMTER));
		break;
	case CharacterID::Robot:
		SetParameter(
			data.hp = ParameterCSV.GetValue(MAX_HP, ROBOT_PARAMTER),
			data.attack = ParameterCSV.GetValue(ATTACK, ROBOT_PARAMTER),
			data.defense = ParameterCSV.GetValue(DEFENCE, ROBOT_PARAMTER));
		break;
	case CharacterID::NormalEnemy:
		SetParameter(
			data.hp = ParameterCSV.GetValue(MAX_HP, NORMALENEMY_PARAMTER),
			data.attack = ParameterCSV.GetValue(ATTACK, NORMALENEMY_PARAMTER),
			data.defense = ParameterCSV.GetValue(DEFENCE, NORMALENEMY_PARAMTER));
		break;
	case CharacterID::EnemyBoss:
		SetParameter(
			data.hp = ParameterCSV.GetValue(MAX_HP, BOSSENEMY_PARAMTER),
			data.attack = ParameterCSV.GetValue(ATTACK, BOSSENEMY_PARAMTER),
			data.defense = ParameterCSV.GetValue(DEFENCE, BOSSENEMY_PARAMTER));
		break;
	default:

		break;
	}

	return data;
}

int CharacterBase::GetParameterValue(CharacterID id, CharacterStatus status)
{
	switch (id)
	{
	case CharacterID::Player:
		value = GetPlayerStatusValue(status);
		break;
	case CharacterID::Robot:
		value = GetRobotStatusValue(status);
		break;
	case CharacterID::NormalEnemy:
		value = GetNormalEnemyStatusValue(status);
		break;
	case CharacterID::EnemyBoss:
		value = GetBossEnemyStatusValue(status);
		break;
	default:

		break;
	}

	return value;
}

void CharacterBase::SetParameter(int hp_, int attack_, int defense_)
{
	parameter.hp = hp_;
	parameter.attack = attack_;
	parameter.defense = defense_;
}

void CharacterBase::SoundEffectLoad(SoundEffect effect)
{
	SceneManager* pManager = (SceneManager*)FindObject("SceneManager");
	GameSound* pSound = pManager->GetSound();

	pSound->EffectLoad(effect);
}

void CharacterBase::SoundEffectPlay(SoundEffect effect)
{
	SceneManager* pManager = (SceneManager*)FindObject("SceneManager");
	GameSound* pSound = pManager->GetSound();

	pSound->EffectPlay(effect);
}

void CharacterBase::SoundEffectStop(SoundEffect effect)
{
	SceneManager* pManager = (SceneManager*)FindObject("SceneManager");
	GameSound* pSound = pManager->GetSound();

	pSound->EffectStop(effect);
}

bool CharacterBase::IsSoundEffectStop(SoundEffect effect)
{
	SceneManager* pManager = (SceneManager*)FindObject("SceneManager");
	GameSound* pSound = pManager->GetSound();

	return pSound->GetEffectFlg(effect);
}

int CharacterBase::GetPlayerStatusValue(CharacterStatus status)
{
	switch (status)
	{
	case CharacterStatus::HP:
		return ParameterCSV.GetValue(MAX_HP, PLAYER_PARAMTER);
		break;
	case CharacterStatus::AttackPower:
		return ParameterCSV.GetValue(ATTACK, PLAYER_PARAMTER);
		break;
	case CharacterStatus::DefensePower:
		return ParameterCSV.GetValue(DEFENCE, PLAYER_PARAMTER);
		break;
	}
}

int CharacterBase::GetRobotStatusValue(CharacterStatus status)
{
	switch (status)
	{
	case CharacterStatus::HP:
		return ParameterCSV.GetValue(MAX_HP, ROBOT_PARAMTER);
		break;
	case CharacterStatus::AttackPower:
		return ParameterCSV.GetValue(ATTACK, ROBOT_PARAMTER);
		break;
	case CharacterStatus::DefensePower:
		return ParameterCSV.GetValue(DEFENCE, ROBOT_PARAMTER);
		break;
	}
}

int CharacterBase::GetNormalEnemyStatusValue(CharacterStatus status)
{
	switch (status)
	{
	case CharacterStatus::HP:
		return ParameterCSV.GetValue(MAX_HP, NORMALENEMY_PARAMTER);
		break;
	case CharacterStatus::AttackPower:
		return ParameterCSV.GetValue(ATTACK, NORMALENEMY_PARAMTER);
		break;
	case CharacterStatus::DefensePower:
		return ParameterCSV.GetValue(DEFENCE, NORMALENEMY_PARAMTER);
		break;
	}
}

int CharacterBase::GetBossEnemyStatusValue(CharacterStatus status)
{
	switch (status)
	{
	case CharacterStatus::HP:
		return ParameterCSV.GetValue(MAX_HP, BOSSENEMY_PARAMTER);
		break;
	case CharacterStatus::AttackPower:
		return ParameterCSV.GetValue(ATTACK, BOSSENEMY_PARAMTER);
		break;
	case CharacterStatus::DefensePower:
		return ParameterCSV.GetValue(DEFENCE, BOSSENEMY_PARAMTER);
		break;
	}
}

float CharacterBase::GetInternalData(CharacterID id, int cal)
{
	switch (id)
	{
	case CharacterID::Player:
		internalData = PlayerInternalDataCSV.GetValue(cal, INTERNALDATA);
		break;
	case CharacterID::Robot:
		internalData = RobotInternalDataCSV.GetValue(cal, INTERNALDATA);
		break;
	case CharacterID::NormalEnemy:
		internalData = EnemyInternalDataCSV.GetValue(cal, INTERNALDATA);
		break;
	case CharacterID::EnemyBoss:
		internalData = EnemyBossInternalDataCSV.GetValue(cal, INTERNALDATA);
		break;
	default:
		break;
	}

	return internalData;
}

int CharacterBase::GetColumnCalCount(CharacterID id)
{
	switch (id)
	{
	case CharacterID::Player:
		calCount = PlayerInternalDataCSV.GetColumnCalCount(INTERNALDATA);
		break;
	case CharacterID::Robot:
		calCount = RobotInternalDataCSV.GetColumnCalCount(INTERNALDATA);
		break;
	case CharacterID::NormalEnemy:
		calCount = EnemyInternalDataCSV.GetColumnCalCount(INTERNALDATA);
		break;
	case CharacterID::EnemyBoss:
		calCount = EnemyBossInternalDataCSV.GetColumnCalCount(INTERNALDATA);
		break;
	default:
		break;
	}

	return calCount;
}

bool CharacterBase::IsMoveLimit(XMFLOAT3 position)
{
	const float CIRCLE_RANGE = 3600.0f;	// バトルフィールドの範囲

	float moveLimit = (position.x * position.x) + (position.z * position.z);

	// 範囲内かどうかをチェック
	if (moveLimit >= CIRCLE_RANGE)
	{
		return true;
	}
	
	return false;
}

void CharacterBase::ChangeStateForIdle()
{
	bool isTrueState = false;

	// すべての状態フラグが立っていないかどうかを調べる
	for (unsigned int nowState = (unsigned int)CharacterState::Idle; nowState <= (unsigned int)CharacterState::MAX_CharacterState; nowState++)
	{
		CharacterState nowAction = (CharacterState)nowState;

		// 状態フラグが立っているかどうかをチェックする
		if (IsStateSet(nowAction))
		{
			isTrueState = true;
		}
	}

	if (isTrueState == false)
	{
		ChangeState(CharacterState::Idle);
	}
}
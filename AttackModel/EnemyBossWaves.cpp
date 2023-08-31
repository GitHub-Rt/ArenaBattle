#include "EnemyBossWaves.h"

#include "../Character/EnemyBoss.h"
#include "../Character/Player.h"

// �萔�錾
const float FIRST_RADIUS = 9.0f;	// �����l�̔��a
const FLOAT WAVES_LENGTH = 1.0f;    // �g��U���̃��f���̒���
const FLOAT CIRCLE_RANGE = 60.0f;   // �ړ��\�͈͂̔��a  

EnemyBossWaves::EnemyBossWaves(GameObject* parent)
	: AttackModelBase(parent, "EnemyBossWaves")
{
	pBoss = nullptr;
	pPlayer = nullptr;
	scalingTimer = 0;
	inside = 0;
	outside = 0;
}

EnemyBossWaves::~EnemyBossWaves()
{

}

void EnemyBossWaves::Initialize()
{
	AttackModelLoad("enemyBossRing.fbx");

	pBoss = (EnemyBoss*)FindObject("EnemyBoss");
	pPlayer = (Player*)FindObject("Player");

	// �����蔻��ϐ��̏�����
	inside = FIRST_RADIUS;
	outside = CIRCLE_RANGE - (FIRST_RADIUS + WAVES_LENGTH);
}

void EnemyBossWaves::AttackModelUpdate()
{
	const int MAX_SCALING_TIME = 45;				// �g��ő厞��
	const float SCALING_STEP = 0.096f;				// �g�呝����
	const float SCALING_STEP_SECOND = 0.049f;		// �g�呝����(���`��)
	const float HIT_TEST_STEP = 0.91f;				// �����蔻�葝����

	// �ő厞�ԓ��Ȃ烂�f�����g��A���ԊO�Ȃ����
	if (scalingTimer < MAX_SCALING_TIME)
	{
		scalingTimer++;

		//// �`�ԕʂɊg�傷��
		//if (pBoss->GetAIState() == BossAIState::Caution)
		//{
		//	// ���`�Ԃ̃��f���̊g��
		//	transform_.scale_.x += SCALING_STEP_SECOND;
		//	transform_.scale_.z += SCALING_STEP_SECOND;
		//}
		//else
		//{
		//	// ���`�Ԃ̃��f���̊g��
		//	transform_.scale_.x += SCALING_STEP;
		//	transform_.scale_.z += SCALING_STEP;
		//}
		
		transform_.scale_.z += SCALING_STEP;
		transform_.scale_.x += SCALING_STEP;

		// �����蔻��ϐ��X�V
		inside += HIT_TEST_STEP;
		outside -= HIT_TEST_STEP;
	}
	else
	{
		scalingTimer = 0;
		KillMe();
	}

	// �v���C���[�Ƃ̓����蔻��
	if (IsCollisionToPlayer())
	{
		// �_���[�W���[�V�����x�N�g���̍쐬
		XMFLOAT3 center = XMFLOAT3(0, 0, 0);
		XMFLOAT3 pos = pPlayer->GetPosition();
		XMVECTOR vDirection = XMLoadFloat3(&pos) - XMLoadFloat3(&center);

		pBoss->AttackModelDamageToPlayer(BossAttackModelHandle::Wave, vDirection);
	}
}

bool EnemyBossWaves::IsCollisionToPlayer()
{
	pPlayer = (Player*)FindObject("Player");

	// �v���C���[�̃|�W�V�����Ƃ̒����𒲂ׂ�
	XMFLOAT3 center = pBoss->GetPosition();
	XMFLOAT3 targetPos = pPlayer->GetPosition();

	XMVECTOR vCenter = XMLoadFloat3(&center);
	XMVECTOR vTarget = XMLoadFloat3(&targetPos);

	XMVECTOR vDirection = vCenter - vTarget;
	vDirection = XMVector3Length(vDirection);

	float length = XMVectorGetX(vDirection);
	length -= FIRST_RADIUS;


	// �v���C���[�Ƃ̓����蔻��
	// �����ɂ��邩�ǂ���
	if (inside < length)
	{
		return false;
	}
	else
	{
		length -= inside;

		// ���f����ɂ��āA�v���C���[�̏�Ԃ��W�����v�ł͂Ȃ����ǂ���
		if (length <= WAVES_LENGTH && pPlayer->IsStateSet(CharacterState::Jumping) == false )
		{
			return true;
		}
	}

	return false;
}
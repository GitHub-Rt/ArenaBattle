#include "RobotBullet.h"
#include "../Character/Robot.h"

#include "../Scene/SceneManager.h"
enum class SCENE_ID;

// íËêîêÈåæ
const XMFLOAT3 HIT_TEST_RANGE = XMFLOAT3(1, 1, 1);


RobotBullet::RobotBullet(GameObject* parent)
	: AttackModelBase(parent, "RobotBullet")
{
    pRobot = nullptr;
    timer = 0;
    travelingDirection = XMFLOAT3(0, 0, 0);
}

RobotBullet::~RobotBullet()
{

}

void RobotBullet::Initialize()
{
	AttackModelLoad("robotBullet.fbx");
	AttackModelAddBoxCollider(HIT_TEST_RANGE);

    InitialPositionPreference();
}

void RobotBullet::AttackModelUpdate()
{
    const float MOVING_VECTOR_MAGNIFICATION = 1.5f;        // à⁄ìÆÉxÉNÉgÉãî{ó¶
    const int BULLET_MAX_TIMER = 120;                      // íeÇ™è¡Ç¶ÇÈÇ‹Ç≈ÇÃéûä‘

    travelingDirection.y = 0;

    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR vMove = XMLoadFloat3(&travelingDirection);

    vMove = XMVector3Normalize(vMove);
    vMove *= MOVING_VECTOR_MAGNIFICATION;

    XMFLOAT3 nextPos = XMFLOAT3(0, 0, 0);
    XMStoreFloat3(&nextPos, vPos + vMove);

    if (GetSceneID() == SCENE_ID::SCENE_ID_BATTLE || GetSceneID() == SCENE_ID::SCENE_ID_DEBUG)
    {
        if (IsMoveLimit(nextPos))
        {
            KillMe();
        }
        else
        {
            transform_.position_ = nextPos;
        }
    }
    else
    {
        if (timer < BULLET_MAX_TIMER)
        {
            timer++;
            transform_.position_ = nextPos;
        }
        else
        {
            KillMe();
        }
    }
}

void RobotBullet::InitialPositionPreference()
{
    pRobot = (Robot*)FindObject("Robot");
    XMFLOAT3 pos = Transform::Float3Add(pRobot->GetParent()->GetPosition(), pRobot->GetPosition());
    XMVECTOR vPos = XMLoadFloat3(&pos);
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(pRobot->GetParent()->GetRotate().y));
    vPos = XMVector3TransformCoord(vPos, mRotate);
    XMStoreFloat3(&transform_.position_, vPos);
}
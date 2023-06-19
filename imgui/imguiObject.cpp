#include "imguiObject.h"
#include "imgui.h"

#include "../Character/Player.h"
#include "../Character/Robot.h"


imguiObject::imguiObject(GameObject* parent)
    :GameObject(parent, "imguiObject")
{
    pPlayer = nullptr;
    pRobot = nullptr;
}

imguiObject::~imguiObject()
{
}

void imguiObject::Initialize()
{
    stateStr = "CharacterState : ";
    attackStateStr = "AttackState : ";
}

void imguiObject::Update()
{
#ifdef _DEBUG

    ImGui::Begin("Master");

    // デバッグ機能
    if (ImGui::TreeNode("DebugMaster"))
    {

        ImGui::TreePop();
    }

    // オブジェクト情報
    if (ImGui::TreeNode("ObjectInformation"))
    {
        // プレイヤー情報
        if (ImGui::TreeNode("PlayerInformation"))
        {
            pPlayer = (Player*)FindObject("Player");
            if (pPlayer != nullptr)
            {
                ImGui::Text("position_x : %g", pPlayer->GetPosition().x);
                ImGui::Text("position_y : %g", pPlayer->GetPosition().y);
                ImGui::Text("position_z : %g", pPlayer->GetPosition().z);

                // カメラ周り
                XMFLOAT3 camPos = pPlayer->GetCameraPosition();
                ImGui::Text("CameraPosition: %g, %g, %g",camPos.x,camPos.y,camPos.z);

                XMFLOAT3 camFoc = pPlayer->GetCameraTarget();
                ImGui::Text("CameraTarget:%g, %g, %g", camFoc.x, camFoc.y, camFoc.z);

                std::string str = GetCharacterStateString(pPlayer);
                ImGui::Text(str.c_str());

                std::string attack = GetPlayerAttackStateString();
                ImGui::Text(attack.c_str());
            }

            ImGui::TreePop();
        }

        // ロボット情報
        if (ImGui::TreeNode("RobotInformation"))
        {
            pRobot = (Robot*)FindObject("Robot");
            if (pRobot != nullptr)
            {
                ImGui::Text("position_x : %g", pRobot->GetPosition().x);
                ImGui::Text("position_y : %g", pRobot->GetPosition().y);
                ImGui::Text("position_z : %g", pRobot->GetPosition().z);

                std::string str = GetCharacterStateString(pRobot);
                ImGui::Text(str.c_str());
            }

            ImGui::TreePop();
        }
        

        ImGui::TreePop();
    }

    ImGui::End();

#endif
}

void imguiObject::Draw()
{
}

void imguiObject::Release()
{
}

std::string imguiObject::GetCharacterStateString(CharacterBase* pTarget)
{
    // 状態のビットフラグ
    unsigned int stateFlg = 0;

    // 状態を表すテキスト
    std::string nowState = "";

    // 各状態のフラグが立っているかどうかを調べるためにループ文で各要素を回す
    for (unsigned int checkFlg = (unsigned int)CharacterState::Idle; checkFlg <= (unsigned int)CharacterState::MAX_CharacterState; checkFlg++)
    {
        
        CharacterState check = (CharacterState)checkFlg;

        // 状態フラグが立ってたら
        if (pTarget->IsStateSet(check))
        {
            // 状態に応じたテキストを追加
            switch (check)
            {
            case CharacterState::Idle:
                nowState += "Idle";
                break;
            case CharacterState::Moving:
                nowState += "Moving, ";
                break;
            case CharacterState::Attacking:
                nowState += "Attacking, ";
                break;
            case CharacterState::Damaged:
                nowState += "Damaged, ";
                break;
            case CharacterState::Jumping:
                nowState += "Jumping, ";
                break;
            case CharacterState::Dodging:
                nowState += "Dodging, ";
                break;
            default:
                break;
            }
        }
    }

    if (nowState == "")
    {
        nowState = "Unknown";
    }

    return stateStr + nowState;

}

std::string imguiObject::GetPlayerAttackStateString()
{
    std::string nowAttackState = "";

    AttackState nowState = pPlayer->GetAttackState();

    switch (nowState)
    {
    case AttackState::NoAttack:
        nowAttackState = "NoAttack";
        break;
    case AttackState::NormalAttack:
        nowAttackState = "NormalAttack";
        break;
    case AttackState::HardAttack:
        nowAttackState = "HardAttack";
        break;
    default:
        break;
    }

    return attackStateStr + nowAttackState;
}

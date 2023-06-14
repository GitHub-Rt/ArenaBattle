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

                CharacterState robotState = pPlayer->GetCharacterState();
                std::string nowState = GetCharacterStateString(robotState);
                std::string str = stateStr + nowState;
                ImGui::Text(str.c_str());
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

                CharacterState robotState = pRobot->GetCharacterState();
                std::string nowState = GetCharacterStateString(robotState);
                std::string str = stateStr + nowState;
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

std::string imguiObject::GetCharacterStateString(CharacterState state)
{
    switch (state)
    {
    case CharacterState::Idle:
        return "Idle";
        break;
    case CharacterState::Moving:
        return "Moving";
        break;
    case CharacterState::Attacking:
        return "Attacking";
        break;
    case CharacterState::Damaged:
        return "Damaged";
        break;
    default:
        return "Unknown";
        break;
    }
}
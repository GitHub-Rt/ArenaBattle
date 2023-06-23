#include "imguiObject.h"
#include "imgui.h"

#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"


imguiObject::imguiObject(GameObject* parent)
    :GameObject(parent, "imguiObject")
{
    pPlayer = nullptr;
    pRobot = nullptr;
    pEnemy = nullptr;
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

                ImGui::Text("HP : %g", pPlayer->GetHP());

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

        // Enemy情報
        if (ImGui::TreeNode("EnemyInformation"))
        {
            pEnemy = (Enemy*)FindObject("Enemy");
            if (pEnemy != nullptr)
            {
                ImGui::Text("position_x : %g", pEnemy->GetPosition().x);
                ImGui::Text("position_y : %g", pEnemy->GetPosition().y);
                ImGui::Text("position_z : %g", pEnemy->GetPosition().z);

                ImGui::Text("HP : %g", pEnemy->GetHP());

                std::string str = GetCharacterStateString(pEnemy);
                ImGui::Text(str.c_str());

                static float x = 0.0f;
                if (ImGui::SliderFloat("float", &x, -1.0f, 1.0f)) {
                    printf("SliderFloat\n");
                    pEnemy->SetDebugPos(x, pEnemy->getDebugPos().y);
                }

                ImGui::Text("gaugePos_x : %g", pEnemy->getDebugPos().x);
                ImGui::Text("gaugePos_y : %g", pEnemy->getDebugPos().y);
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

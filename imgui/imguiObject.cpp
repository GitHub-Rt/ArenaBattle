#include "imguiObject.h"
#include "imgui.h"

#include "../Character/Player.h"
#include "../Character/Robot.h"
#include "../Character/Enemy.h"
#include "../Character/EnemyBoss.h"

#include "../Manager/EnemyManager.h"

#include "../Scene/SceneManager.h"

#include <stdio.h>

imguiObject::imguiObject(GameObject* parent)
    :GameObject(parent, "imguiObject")
{
    pPlayer = nullptr;
    pRobot = nullptr;
    pEnemy = nullptr;
    pBoss = nullptr;

    isImmortality = true;
    isGameLevelHard = false;
}

imguiObject::~imguiObject()
{
}

void imguiObject::Initialize()
{
#ifdef _DEBUG

    stateStr = "CharacterState : ";
    attackStateStr = "AttackState : ";
    aiStateStr = "AIState : ";

    // プレイヤーを不死にするかどうか
    if (isImmortality)
    {
        pPlayer = (Player*)FindObject("Player");
        pPlayer->Immortality();
    }

#endif
}

void imguiObject::Update()
{
#ifdef _DEBUG

    ImGui::Begin("Master");

    // デバッグ機能
    if (ImGui::TreeNode("DebugMaster"))
    {

        // 難易度選択
        if (ImGui::TreeNode("GameLevel"))
        {
            static bool isChangeMode = false;

            // 難易度変更のチェックボックス
            ImGui::Checkbox("GameLeveltoHard", &isGameLevelHard);

            // HardModeでSceneをリロードする
            if (isGameLevelHard && isChangeMode == false)
            {
                isChangeMode = true;

                SceneManager* pManager = (SceneManager*)FindObject("SceneManager");
                pManager->SetHardModeFlg();
                pManager->ReLoadScene(SCENE_ID::SCENE_ID_DEBUG);
            }
            else if (isGameLevelHard == false && isChangeMode)
            {
                isChangeMode = false;

                // EasyモードでSceneをリロードする
                SceneManager* pManager = (SceneManager*)FindObject("SceneManager");
                pManager->ReLoadScene(SCENE_ID::SCENE_ID_DEBUG);
            }


            ImGui::TreePop();
        }

        // 敵ボス
        if (ImGui::TreeNode("EnemyBossDebug"))
        {
            // 攻撃手段
            if (ImGui::TreeNode("EnemyBossAttack"))
            {
                // 攻撃手段を未攻撃で初期化する
                static int attackNum = 1;

                // 現在攻撃を保存する
                pBoss = (EnemyBoss*)FindObject("EnemyBoss");
                int prevAttack = pBoss->GetAttackState();

                // 攻撃手段を設定する
                ImGui::RadioButton("NoAttack", &attackNum, (int)BossAttackState::NoAttack);
                ImGui::SameLine();
                ImGui::RadioButton("BulletAttack", &attackNum, (int)BossAttackState::BulletAttack);
                
                ImGui::RadioButton("SpiralMoveAttack", &attackNum, (int)BossAttackState::SpiralMoveAttack);
                ImGui::SameLine();
                ImGui::RadioButton("WavesAttack", &attackNum, (int)BossAttackState::WavesAttack);

                ImGui::RadioButton("JumpAttack", &attackNum, (int)BossAttackState::JumpAttack);
                ImGui::SameLine();
                ImGui::RadioButton("SpecialAttack", &attackNum, (int)BossAttackState::SpecialAttack);

                // 該当攻撃を行う用にセットする
                if (prevAttack != attackNum)
                {
                    // 初期位置に戻す
                    pBoss->ReturnFirstPos();
                    if (pBoss->IsFirstPosAround(pBoss->GetPosition()))
                    {
                        // 攻撃変数を初期化して選択した新しい攻撃を開始させる
                        pBoss->AttackVariableReset((BossAttackState)prevAttack);
                        pBoss->SetAttackSlect((BossAttackState)attackNum);
                    }
                    
                }

                ImGui::TreePop();
            }

            // AIレベル
            if (ImGui::TreeNode("EnemyBossAILevel"))
            {
                // AIレベルを余裕で初期化する
                static int aiLevel = 1;

                // AIレベル選択RadioButton
                ImGui::RadioButton("Allowance", &aiLevel, (int)BossAIState::Allowance);
                ImGui::SameLine();
                ImGui::RadioButton("Normal", &aiLevel, (int)BossAIState::Normal);
                ImGui::SameLine();
                ImGui::RadioButton("Caution", &aiLevel, (int)BossAIState::Caution);

                // 選択したAIレベルに変更する
                pBoss = (EnemyBoss*)FindObject("EnemyBoss");
                pBoss->SetAIState((BossAIState)aiLevel);


                ImGui::TreePop();
            }


            ImGui::TreePop();
        }



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
                /*ImGui::Text("position_x : %g", pRobot->GetPosition().x);
                ImGui::Text("position_y : %g", pRobot->GetPosition().y);
                ImGui::Text("position_z : %g", pRobot->GetPosition().z);*/

                std::string str = GetCharacterStateString(pRobot);
                ImGui::Text(str.c_str());
            }

            ImGui::TreePop();
        }

        // Enemy情報
        if (ImGui::TreeNode("EnemyInformation"))
        {
            if (EnemyManager::IsListEmpty() == false)
            {
                int size = EnemyManager::GetVectorSize();
                for (int i = 0; i < size; i++)
                {
                    char numStr[256];
                    sprintf_s(numStr, "IndexNumber : %d", i);

                    if (ImGui::TreeNode(numStr))
                    {
                        // Enemy情報をvectorから取得
                        pEnemy = EnemyManager::GetEnemyContent(i);

                        // 実際の各Enemy情報
                        if (pEnemy != nullptr)
                        {
                            std::string str = GetCharacterStateString(pEnemy);
                            ImGui::Text(str.c_str());

                            ImGui::Text("HP : %g", pEnemy->GetHP());

                            ImGui::Text("position_x : %g", pEnemy->GetPosition().x);
                            ImGui::Text("position_y : %g", pEnemy->GetPosition().y);
                            ImGui::Text("position_z : %g", pEnemy->GetPosition().z);


                            std::string damegeStr = "isDamage : ";
                            if (pEnemy->IsDamage())
                            {
                                damegeStr += "true";
                            }
                            else
                            {
                                damegeStr += "false";
                            }
                            ImGui::Text(damegeStr.c_str());
                        }

                        ImGui::TreePop();
                    }
                }
            }
           

            ImGui::TreePop();
        }

        // EnemyBoss情報
        if (ImGui::TreeNode("EnemyBossInformation"))
        {
           pBoss = (EnemyBoss*)FindObject("EnemyBoss");

            if (pBoss != nullptr)
            {
                ImGui::Text("position_x : %g", pBoss->GetPosition().x);
                ImGui::Text("position_y : %g", pBoss->GetPosition().y);
                ImGui::Text("position_z : %g", pBoss->GetPosition().z);

                ImGui::Text("HP : %g", pBoss->GetHP());

                std::string str = GetCharacterStateString(pBoss);
                ImGui::Text(str.c_str());

                std::string attack = GetEnemyBossAttackStateString();
                ImGui::Text(attack.c_str());

                std::string ai = GetAIStateString();
                ImGui::Text(ai.c_str());
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

std::string imguiObject::GetEnemyBossAttackStateString()
{
    std::string nowAttackState = "";

    for (unsigned int nowState = (unsigned int)BossAttackState::NoAttack; nowState <= (unsigned int)BossAttackState::MaxAttackState; nowState++)
    {
        BossAttackState nowAttack = (BossAttackState)nowState;

        if (pBoss->IsAttackState(nowAttack))
        {
            switch (nowAttack)
            {
            case BossAttackState::NoAttack:
                nowAttackState = "NoAttack";
                break;
            case BossAttackState::BulletAttack:
                nowAttackState += "BulletAttack, ";
                break;
            case BossAttackState::SpiralMoveAttack:
                nowAttackState += "SpiralMoveAttack, ";
                break;
            case BossAttackState::WavesAttack:
                nowAttackState += "WavesAttack, ";
                break;
            case BossAttackState::JumpAttack:
                nowAttackState += "JumpAttack, ";
                break;
            case BossAttackState::SpecialAttack:
                nowAttackState = "SpecialAttack, ";
                break;
            default:
                break;
            }
        }
    }
    
    if (nowAttackState == "")
    {
        nowAttackState = "Unknown";
    }

    return attackStateStr + nowAttackState;
}

std::string imguiObject::GetAIStateString()
{
    std::string nowAIState = "";

    BossAIState nowState = pBoss->GetAIState();

    switch (nowState)
    {
    case BossAIState::Allowance:
        nowAIState = "Allowance";
        break;
    case BossAIState::Normal:
        nowAIState = "Normal";
        break;
    case BossAIState::Caution:
        nowAIState = "Caution";
        break;
    default:
        break;
    }

    if (nowAIState == "")
    {
        nowAIState = "Unknown";
    }

    return aiStateStr + nowAIState;
}
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

    // �v���C���[��s���ɂ��邩�ǂ���
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

    // �f�o�b�O�@�\
    if (ImGui::TreeNode("DebugMaster"))
    {

        // ��Փx�I��
        if (ImGui::TreeNode("GameLevel"))
        {
            static bool isChangeMode = false;

            // ��Փx�ύX�̃`�F�b�N�{�b�N�X
            ImGui::Checkbox("GameLeveltoHard", &isGameLevelHard);

            // HardMode��Scene�������[�h����
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

                // Easy���[�h��Scene�������[�h����
                SceneManager* pManager = (SceneManager*)FindObject("SceneManager");
                pManager->ReLoadScene(SCENE_ID::SCENE_ID_DEBUG);
            }


            ImGui::TreePop();
        }

        // �G�{�X
        if (ImGui::TreeNode("EnemyBossDebug"))
        {
            // �U����i
            if (ImGui::TreeNode("EnemyBossAttack"))
            {
                // �U����i�𖢍U���ŏ���������
                static int attackNum = 1;

                // ���ݍU����ۑ�����
                pBoss = (EnemyBoss*)FindObject("EnemyBoss");
                int prevAttack = pBoss->GetAttackState();

                // �U����i��ݒ肷��
                ImGui::RadioButton("NoAttack", &attackNum, (int)BossAttackState::NoAttack);
                ImGui::SameLine();
                ImGui::RadioButton("BulletAttack", &attackNum, (int)BossAttackState::BulletAttack);
                
                ImGui::RadioButton("SpiralMoveAttack", &attackNum, (int)BossAttackState::SpiralMoveAttack);
                ImGui::SameLine();
                ImGui::RadioButton("WavesAttack", &attackNum, (int)BossAttackState::WavesAttack);

                ImGui::RadioButton("JumpAttack", &attackNum, (int)BossAttackState::JumpAttack);
                ImGui::SameLine();
                ImGui::RadioButton("SpecialAttack", &attackNum, (int)BossAttackState::SpecialAttack);

                // �Y���U�����s���p�ɃZ�b�g����
                if (prevAttack != attackNum)
                {
                    // �����ʒu�ɖ߂�
                    pBoss->ReturnFirstPos();
                    if (pBoss->IsFirstPosAround(pBoss->GetPosition()))
                    {
                        // �U���ϐ������������đI�������V�����U�����J�n������
                        pBoss->AttackVariableReset((BossAttackState)prevAttack);
                        pBoss->SetAttackSlect((BossAttackState)attackNum);
                    }
                    
                }

                ImGui::TreePop();
            }

            // AI���x��
            if (ImGui::TreeNode("EnemyBossAILevel"))
            {
                // AI���x����]�T�ŏ���������
                static int aiLevel = 1;

                // AI���x���I��RadioButton
                ImGui::RadioButton("Allowance", &aiLevel, (int)BossAIState::Allowance);
                ImGui::SameLine();
                ImGui::RadioButton("Normal", &aiLevel, (int)BossAIState::Normal);
                ImGui::SameLine();
                ImGui::RadioButton("Caution", &aiLevel, (int)BossAIState::Caution);

                // �I������AI���x���ɕύX����
                pBoss = (EnemyBoss*)FindObject("EnemyBoss");
                pBoss->SetAIState((BossAIState)aiLevel);


                ImGui::TreePop();
            }


            ImGui::TreePop();
        }



        ImGui::TreePop();
    }

    // �I�u�W�F�N�g���
    if (ImGui::TreeNode("ObjectInformation"))
    {
        // �v���C���[���
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

        // ���{�b�g���
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

        // Enemy���
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
                        // Enemy����vector����擾
                        pEnemy = EnemyManager::GetEnemyContent(i);

                        // ���ۂ̊eEnemy���
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

        // EnemyBoss���
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
    // ��Ԃ̃r�b�g�t���O
    unsigned int stateFlg = 0;

    // ��Ԃ�\���e�L�X�g
    std::string nowState = "";

    // �e��Ԃ̃t���O�������Ă��邩�ǂ����𒲂ׂ邽�߂Ƀ��[�v���Ŋe�v�f����
    for (unsigned int checkFlg = (unsigned int)CharacterState::Idle; checkFlg <= (unsigned int)CharacterState::MAX_CharacterState; checkFlg++)
    {
        
        CharacterState check = (CharacterState)checkFlg;

        // ��ԃt���O�������Ă���
        if (pTarget->IsStateSet(check))
        {
            // ��Ԃɉ������e�L�X�g��ǉ�
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
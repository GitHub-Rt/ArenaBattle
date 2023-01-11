#include "imguiObject.h"
#include "imgui.h"

#include "../Engine/Global.h"

#include "../Player/Player.h"
#include "../Enemy/Boss/EnemyBoss.h"

//コンストラクタ
imguiObject::imguiObject(GameObject* parent)
    :GameObject(parent, "imguiObject")
{
}

//デストラクタ
imguiObject::~imguiObject()
{
}

//初期化
void imguiObject::Initialize()
{
}

//更新
void imguiObject::Update()
{
    //プレイヤー情報
    {
        ImGui::Begin("Player");
        Player* pPlayer = (Player*)FindObject("Player");
        if (pPlayer != nullptr)
        {
            ImGui::Text("position_x : %g", pPlayer->GetPosition().x);
            ImGui::Text("position_y : %g", pPlayer->GetPosition().y);
            ImGui::Text("position_z : %g", pPlayer->GetPosition().z);


            ImGui::Text("HP : %g", pPlayer->GetHP());

            ImGui::Text("AttackNum(1:NormalAttack,2:HardAttack) : %d", pPlayer->GetAttackPattern());


            pPlayer->Release();

        }
        
        SAFE_RELEASE(pPlayer);
        ImGui::End();
    }

    //敵ボス情報
    {
        ImGui::Begin("EnemyBoss");
        EnemyBoss* pBoss = (EnemyBoss*)FindObject("EnemyBoss");
        if (pBoss != nullptr)
        {

            ImGui::Text("position_x : %g", pBoss->GetPosition().x);
            ImGui::Text("position_y : %g", pBoss->GetPosition().y);
            ImGui::Text("position_z : %g", pBoss->GetPosition().z);


            ImGui::Text("AttackNum : %d", pBoss->GetAttackPattern());


            pBoss->Release();
        }
        
        SAFE_RELEASE(pBoss);
        ImGui::End();
    }
}

//描画
void imguiObject::Draw()
{
    
}

//開放
void imguiObject::Release()
{
}
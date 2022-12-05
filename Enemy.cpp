#include "Enemy.h"
#include "Stage.h"
#include "Player.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/Global.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"


#include <cstdlib>


//コンストラクタ
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1),someFlag(1)
{
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{
    //乱数の初期化、範囲選択
    std::srand((unsigned)time(NULL));
    float randPos = rand() % 10 + 1;

    //モデルデータのロード
    hModel_ = Model::Load("enemy.fbx");
    assert(hModel_ >= 0);

    //出現位置
    if(randPos < 5.0f)
    {
        transform_.position_.x -= randPos;
    }
    else
    {
        transform_.position_.x += randPos - 5.0f;
    }
    transform_.position_.z += 10.0f;

    //当たり判定枠
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.2f);
    AddCollider(collision);
}

//更新
void Enemy::Update()
{


    


    //ステージ情報獲得
    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

    //レイをステージに飛ばす
    RayCastData data;
    data.start = transform_.position_;            //レイの発射位置
    data.dir = XMFLOAT3(0.0f, -1.0f, 0.0f);       //レイの方向
    Model::RayCast(hGroundModel, &data);           //レイを発射

    //レイが当たったら
    if (data.hit)
    {
        //位置を下げる
        transform_.position_.y -= (data.dist - HALF_HEIGHT);

    }

    ///////////////////////////　移動  /////////////////////////////


    //プレイヤー、敵の座標を取得
    Player* pPlayer = (Player*)FindObject("Player");

    //生きてるかどうかを確認
    pAlive = pPlayer->PGetAlive();
    if (pAlive == true)
    {
        pCurrentPos = pPlayer->GetPosition();
    }
    else
    {
        //MessageBox(NULL, "プレイヤーが倒されました。OKボタンを押した後にスタートボタンを押してください", "Game Over", MB_OK);

        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_OVER);
    }
    eCurrentPos = GetPosition();


    prevPos = XMLoadFloat3(&eCurrentPos);

    //プレイヤー座標から敵座標を引く
    XMVECTOR vMove = XMLoadFloat3(&pCurrentPos) - prevPos;

    //ベクトルの長さを求める
    XMVECTOR vLength = XMVector3Length(vMove);
    float length = XMVectorGetX(vLength);

    //一定範囲内にいるかどうか
    if (length <= EP_LENGTH)
    {
        //これ以上その先へは進めなくする
        XMStoreFloat3(&transform_.position_, prevPos);

        //攻撃を行う
        //eAttackS_ = true;
    }
    else
    {
        //正規化して移動量をかける
        vMove = XMVector3Normalize(vMove) * amountMove;

        //型変換
        XMStoreFloat3(&nextPos, vMove);

        //移動
        transform_.position_.x += nextPos.x;
        transform_.position_.z += nextPos.z;
    }


    /////////////////////  攻撃   //////////////////////////

    if (eAttackS_ == true)
    {
        

    }


    //HPがなくなったら
    if (HP <= 0)
    {
        HP = MAX_HP;
        someFlag = false;
        KillMe();
    }

}

//描画
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Enemy::Release()
{
    
}

//何かに当たった
void Enemy::OnCollision(GameObject* pTarget)
{
    //当たったときの処理
    //プレイヤーに当たったとき
    if (pTarget->FindObject("Player"))
    {
        
        //プレイヤーの状態確認
        Player* pStatus = (Player*)FindObject("Player");
        pAttackS_ = pStatus->PGetCondition();
        if (pAttackS_ == true)
        {
            pAcom = pStatus->PGetAttack();
            //後でダメージ係数に変えて計算させる
            if (pAcom != NULL)
            {
                //攻撃の種類判別
                switch(pAcom)
                {
                //通常攻撃
                case 1:
                    HP -= 0.25f;
                    break;
                //強攻撃
                case 2:
                    HP -= 0.5f;
                    break;
                }
            }
            pAcom = NULL;
            pStatus->PSetFalse(pAttackS_);
        }
        SAFE_RELEASE(pStatus);
    }
}

XMFLOAT3 Enemy::GetPosition() 
{
    return transform_.position_; 
}

//敵の状態
bool Enemy::EGetCondition()
{
    return eAttackS_; 
}

void Enemy::ESetFalse(bool attackFlg_) 
{
    attackFlg_ = false;
    eAttackS_ = false;
}

bool Enemy::EGetAlive()
{
    return someFlag;
}
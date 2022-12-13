#include "Start.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"
#include "Engine/SceneManager.h"


#include "Enemy.h"
#include "PlayScene.h"
#include "Stage.h"

//コンストラクタ
Start::Start(GameObject* parent)
    :GameObject(parent, "Start"), hModel_(-1)
{
}

//デストラクタ
Start::~Start()
{
}

//初期化
void Start::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("start.fbx");
    assert(hModel_ >= 0);


    transform_.position_.z = 20.0f;

    //当たり判定
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(5, 60, 5));
    AddCollider(collision);
}

//更新
void Start::Update()
{
}

//描画
void Start::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Start::Release()
{
}

//何かに当たった
void Start::OnCollision(GameObject* pTarget)
{
    //当たったときの処理
    if (pTarget->FindObject("Player"))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_BUTTLE);
    }
}
#pragma once
#include "../Engine/GameObject.h"


//imguiを管理するクラス
class imguiObject : public GameObject
{

public:
    //コンストラクタ
    imguiObject(GameObject* parent);

    //デストラクタ
    ~imguiObject();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};
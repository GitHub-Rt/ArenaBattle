#include "ReleaseScene.h"

#include "SceneManager.h"
#include "../UI/BackGroundImage.h"
#include "../UI/ReleaseImage.h"
#include "../UI/SelectBox.h"

#include "../Engine/Input.h"

const float POS_X = -0.0375f;
const float RELEASE_BACK_POS_X = -0.0225f;
const float RELEASE_BACK_Y = 0.0125f;
const float RELEASE_END_Y = -0.35f;

ReleaseScene::ReleaseScene(GameObject* parent)
	: GameObject(parent, "ReleaseScene")
{
	pManager = nullptr;
	pBox = nullptr;
	nowState = ReleaseState::BackGame;
}

ReleaseScene::~ReleaseScene()
{

}

void ReleaseScene::Initialize()
{
	pManager = (SceneManager*)FindObject("SceneManager");

	Instantiate<BackGroundImage>(this);
	Instantiate<ReleaseImage>(this);
	pBox = Instantiate<SelectBox>(this);
	pBox->SetSelectBox(XMFLOAT3(RELEASE_BACK_POS_X, RELEASE_BACK_Y, 0), true);
}

void ReleaseScene::Update()
{
	// 遷移先シーンの選択切り替え(UI表示位置の変更)
	ChangeStateUIPosition();

	// 該当するシーンに遷移する
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN))
	{
		switch (nowState)
		{
		case ReleaseState::BackGame:
			pManager->ChangeScene((SCENE_ID)pManager->GetPrevScene());
			break;
		case ReleaseState::ExitGame:
			PostQuitMessage(0);	//プログラム終了
			break;
		default:
			break;
		}
		
	}



}

void ReleaseScene::Draw()
{

}

void ReleaseScene::Release()
{

}

void ReleaseScene::ChangeStateUIPosition()
{
	// 移行前の状態を保存
	ReleaseState prevState = nowState;

	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_DOWN) || Input::IsKeyDown(DIK_DOWN))
	{
		// 一番下の項目が今の状態ではないかを確認
		if (nowState != ReleaseState::ExitGame)
		{
			// 次の要素に移行
			int now = (int)nowState;
			now++;
			nowState = (ReleaseState)now;
		}
	}
	else if (Input::IsPadButtonDown(XINPUT_GAMEPAD_DPAD_UP) || Input::IsKeyDown(DIK_UP))
	{
		// 一番上の項目が今の状態ではないかを確認
		if (nowState != ReleaseState::BackGame)
		{
			// 1つ前の要素に移行
			int now = (int)nowState;
			now--;
			nowState = (ReleaseState)now;
		}
	}


	// 要素の移行が見られたら 該当要素の位置にUIをセット
	if (prevState != nowState)
	{
		switch (nowState)
		{
		case ReleaseState::BackGame:
			pBox->SetSelectBox(XMFLOAT3(RELEASE_BACK_POS_X, RELEASE_BACK_Y, 0), true);
			break;
		case ReleaseState::ExitGame:
			pBox->SetSelectBox(XMFLOAT3(POS_X, RELEASE_END_Y, 0));
			break;
		default:
			break;
		}
	}
}
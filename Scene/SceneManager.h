#pragma once
#include "../Engine/global.h"
#include "../Engine/GameObject.h"
#include "../Sound/GameSound.h"

//ゲームに登場するシーン
enum class SCENE_ID
{
	SCENE_ID_TITLE,
	SCENE_ID_START,
	SCENE_ID_RELEASE,
	SCENE_ID_KEYBOARDOPERATION,		//コントローラー用操作説明
	SCENE_ID_CONTROLLEROPERATION,	//キーボード用操作説明
	SCENE_ID_PLAY,
	SCENE_ID_BATTLE,
	SCENE_ID_CLEAR,
	SCENE_ID_OVER,
	SCENE_ID_DEBUG,
	MAX_SCENE_ID
};

enum class RetryPoint
{
	NormalEnemyBattle,
	BossBattle,
	BossLastBattle
};

//-----------------------------------------------------------
//シーン切り替えを担当するオブジェクト
//-----------------------------------------------------------
class SceneManager : public GameObject
{
public:
	SceneManager(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//シーン切り替え（実際に切り替わるのはこの次のフレーム）
	//引数：next	次のシーンのID
	void ChangeScene(SCENE_ID next);

	/// <summary>
	/// 前回のシーンIDを取得
	/// </summary>
	/// <returns></returns>
	SCENE_ID GetPrevScene() { return prevSceneID_; }

	/// <summary>
	/// 現在のシーンIDを取得
	/// </summary>
	/// <returns></returns>
	SCENE_ID GetSceneID() { return currentSceneID_; }

	/// <summary>
	/// サウンド情報を取得
	/// </summary>
	/// <returns></returns>
	GameSound* GetSound() { return pSound; }

	// 一周目(Easy)をクリアしたときに呼ぶ関数
	void SetClearedFlg() { isCleared = true; }
	
	// ハードモードにセットする
	void SetHardModeFlg() { isHardMode = true; }

	// シーンの再作成を行う関数
	void ReLoadScene(SCENE_ID targetScene);


	void SetRetryPoint(RetryPoint nextPoint) { nowPoint = nextPoint; }
	RetryPoint GetRetryPoint() { return nowPoint; }

	bool GetClearFlg() { return isCleared; }

	bool GetHardMode() { return isHardMode; }


private:
	SCENE_ID currentSceneID_;	//現在のシーン
	SCENE_ID nextSceneID_;		//次のシーン
	SCENE_ID prevSceneID_;		//前回のシーン

	RetryPoint nowPoint;
	GameSound* pSound;

	bool isCleared;				// クリアしたかどうか
	bool isHardMode;			// ハードモードかどうか
	bool isReLoad;				// 再作成するかどうか
};
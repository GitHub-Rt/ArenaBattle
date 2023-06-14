#pragma once
#include <string>

//-----------------------------------------------------------
//サウンドを管理する（XAudio使用）
//-----------------------------------------------------------
namespace Audio
{
	//初期化
	void Initialize();

	/// <summary>
	/// サウンドファイル(.wav）をロード
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	/// <param name="loopFlg">再生形式(trueで無限ループ、falseで１度のみ再生)</param>
	/// <param name="svNum">同時に鳴らす最大数（省略可）</param>
	/// /// <param name="volume">音量</param>
	/// <returns>すでに同じ名前のファイルをロード済みの場合は、既存のデータの番号を返す</returns>
	int Load(std::string fileName, bool loopFlg,float volume, int svNum = 1);

	//再生
	//引数：handle	鳴らしたいサウンドの番号
	void Play(int ID);

	/// <summary>
	/// 流れてる音楽の停止を行う関数
	/// </summary>
	/// <param name="ID">止めたいサウンドの番号</param>
	void Stop(int ID);

	/// <summary>
	/// 再生終了したかどうかを調べる関数
	/// </summary>
	/// <param name="ID">確認したいサウンドの番号</param>
	/// <returns>終了していたらtrue</returns>
	bool IsEndPlayBack(int ID);

	//すべて開放
	void Release();
	void AllRelease();
};


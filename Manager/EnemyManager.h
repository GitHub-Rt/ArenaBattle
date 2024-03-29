#pragma once
#include <vector>

class Enemy;

namespace EnemyManager
{	
	// リストにEnemyを追加する
	void AddEnemyList(Enemy* enemy);

	// リストから情報を消す
	void RemoveEnemy(Enemy* enemy);

	// リストに該当するEnemyがいるかどうか(存在していたらtrue)
	bool IsTargetEnemy(Enemy* enemy);

	// リスト内が空かどうか(空だったらtrue)
	bool IsListEmpty();

	// リスト内の該当インデックス番号を取得する
	int GetListTargetNumber(Enemy* pEnemy);

	// vectorサイズを取得する
	int GetVectorSize();

	// 該当番号の情報を取得する
	Enemy* GetEnemyContent(int index);

	// リストの全要素を削除する
	void ClearEnemy();

	extern std::vector<Enemy*> enemyList;
};


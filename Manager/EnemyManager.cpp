#include "EnemyManager.h"
#include "../Character/Enemy.h"


namespace EnemyManager {

	std::vector<Enemy*> enemyList;

	void AddEnemyList(Enemy* enemy)
	{
		enemyList.push_back(enemy);
	}

	void RemoveEnemy(Enemy* enemy)
	{
		auto target = std::find(enemyList.begin(), enemyList.end(), enemy);
		if (target != enemyList.end())
		{
			enemyList.erase(target);
		}
	}

	bool IsTargetEnemy(Enemy* enemy)
	{
		auto target = std::find(enemyList.begin(), enemyList.end(), enemy);
		if (target != enemyList.end())
		{
			return true;
		}

		return false;
	}

	bool IsListEmpty()
	{
		for (auto i = enemyList.begin(); i < enemyList.end(); i++)
		{
			if (IsTargetEnemy(*i))
			{
				return false;
			}
		}

		return true;

	}

	int GetListTargetNumber(Enemy* pEnemy)
	{
		auto target = std::find(enemyList.begin(), enemyList.end(), pEnemy);
		if (target != enemyList.end())
		{
			return std::distance(enemyList.begin(), target);
		}

		// �Y�����Ȃ�������A�T�C�Y����1�����l��Ԃ�
		return enemyList.size() + 1;
	}

	int GetVectorSize()
	{
		return enemyList.size();
	}

	Enemy* GetEnemyContent(int index)
	{
		return enemyList[index];
	}

}

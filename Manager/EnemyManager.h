#pragma once
#include <vector>

class Enemy;

namespace EnemyManager
{	
	// ���X�g��Enemy��ǉ�����
	void AddEnemyList(Enemy* enemy);

	// ���X�g�����������
	void RemoveEnemy(Enemy* enemy);

	// ���X�g�ɊY������Enemy�����邩�ǂ���(���݂��Ă�����true)
	bool IsTargetEnemy(Enemy* enemy);

	// ���X�g�����󂩂ǂ���(�󂾂�����true)
	bool IsListEmpty();

	// ���X�g���̊Y���C���f�b�N�X�ԍ����擾����
	int GetListTargetNumber(Enemy* pEnemy);

	// �Y���ԍ��̏����擾����
	Enemy* GetEnemyContent(int index);

	extern std::vector<Enemy*> enemyList;
};


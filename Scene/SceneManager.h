#pragma once
#include "../Engine/global.h"
#include "../Engine/GameObject.h"
#include "../Sound/GameSound.h"

//�Q�[���ɓo�ꂷ��V�[��
enum class SCENE_ID
{
	SCENE_ID_TITLE,
	SCENE_ID_START,
	SCENE_ID_RELEASE,
	SCENE_ID_KEYBOARDOPERATION,		//�R���g���[���[�p�������
	SCENE_ID_CONTROLLEROPERATION,	//�L�[�{�[�h�p�������
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
//�V�[���؂�ւ���S������I�u�W�F�N�g
//-----------------------------------------------------------
class SceneManager : public GameObject
{
public:
	SceneManager(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
	//�����Fnext	���̃V�[����ID
	void ChangeScene(SCENE_ID next);

	/// <summary>
	/// �O��̃V�[��ID���擾
	/// </summary>
	/// <returns></returns>
	SCENE_ID GetPrevScene() { return prevSceneID_; }

	/// <summary>
	/// ���݂̃V�[��ID���擾
	/// </summary>
	/// <returns></returns>
	SCENE_ID GetSceneID() { return currentSceneID_; }

	/// <summary>
	/// �T�E���h�����擾
	/// </summary>
	/// <returns></returns>
	GameSound* GetSound() { return pSound; }

	// �����(Easy)���N���A�����Ƃ��ɌĂԊ֐�
	void SetClearedFlg() { isCleared = true; }
	
	// �n�[�h���[�h�ɃZ�b�g����
	void SetHardModeFlg() { isHardMode = true; }

	// �V�[���̍č쐬���s���֐�
	void ReLoadScene(SCENE_ID targetScene);


	void SetRetryPoint(RetryPoint nextPoint) { nowPoint = nextPoint; }
	RetryPoint GetRetryPoint() { return nowPoint; }

	bool GetClearFlg() { return isCleared; }

	bool GetHardMode() { return isHardMode; }


private:
	SCENE_ID currentSceneID_;	//���݂̃V�[��
	SCENE_ID nextSceneID_;		//���̃V�[��
	SCENE_ID prevSceneID_;		//�O��̃V�[��

	RetryPoint nowPoint;
	GameSound* pSound;

	bool isCleared;				// �N���A�������ǂ���
	bool isHardMode;			// �n�[�h���[�h���ǂ���
	bool isReLoad;				// �č쐬���邩�ǂ���
};
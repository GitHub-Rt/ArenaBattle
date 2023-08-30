#pragma once
#include "../Engine/GameObject.h"

enum class CharacterState;
class CharacterBase;
class Player;
class Robot;
class Enemy;
class EnemyBoss;

class imguiObject : public GameObject
{
public:
    imguiObject(GameObject* parent);
    ~imguiObject();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    std::string GetCharacterStateString(CharacterBase* pTarget);

    std::string GetPlayerAttackStateString();
    std::string GetEnemyBossAttackStateString();
    std::string GetAIStateString();

private:

    Player* pPlayer;
    Robot* pRobot;
    Enemy* pEnemy;
    EnemyBoss* pBoss;

    std::string stateStr;
    std::string attackStateStr;
    std::string aiStateStr;

    bool isImmortality;
    bool isGameLevelHard;
    bool isStopDrawing;
};

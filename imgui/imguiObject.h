#pragma once
#include "../Engine/GameObject.h"

enum class CharacterState;
class Player;
class Robot;

class imguiObject : public GameObject
{
public:
    imguiObject(GameObject* parent);
    ~imguiObject();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    std::string GetCharacterStateString(CharacterState state);

private:

    Player* pPlayer;
    Robot* pRobot;


    std::string stateStr;
};

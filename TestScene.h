#pragma once
#include "Engine/GameObject.h"

class Player;
class Stage;

class TestScene : public GameObject
{
	Player* player_;
	Stage* pStage_;
public:
	TestScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
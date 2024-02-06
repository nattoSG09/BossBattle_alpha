#pragma once
#include "Engine/GameObject.h"

class Button;

class TestScene : public GameObject
{
	Button* pButton_;
public:
	TestScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
#pragma once
#include "Engine/GameObject.h"
#include "Circle.h"

class Ore : public GameObject
{
	int hModel_;
	Circle circle_;
public:
	Ore(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};


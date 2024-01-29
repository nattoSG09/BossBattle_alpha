#pragma once
#include "Engine/GameObject.h"
#include "Circle.h"

class Object02 : public GameObject
{
	int hModel_;
	Circle circle_;
public:
	Object02(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	Circle GetCircle() { return circle_; }
};


#pragma once
#include "Engine/GameObject.h"
#include "Circle.h"

class Object01 : public GameObject
{
	int hCircle_;
	int hOre_;
	Circle circle_;
public:
	Object01(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	Circle GetCircle() { return circle_; }

};
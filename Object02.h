#pragma once
#include "Engine/GameObject.h"
#include "Circle.h"

class Object02 : public GameObject
{
public:
	Object02(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};


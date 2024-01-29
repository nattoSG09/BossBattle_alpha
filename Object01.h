#pragma once
#include "Engine/GameObject.h"

class Object01 : public GameObject
{
	Object01(GameObject* _pParent);
	void Initilize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};


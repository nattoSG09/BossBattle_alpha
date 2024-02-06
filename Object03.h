#pragma once
#include "Engine/GameObject.h"

class Object03 : public GameObject
{
public:
	Object03(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};


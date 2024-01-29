#pragma once
#include "Engine/GameObject.h"

class Object01 : public GameObject
{
	int hModel_;
public:
	Object01(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
#pragma once
#include "Engine/GameObject.h"

class DiamondOre : public GameObject
{
	int hModel_;
public:
	DiamondOre(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};


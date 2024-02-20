#pragma once
#include "Engine/GameObject.h"

class Enemy : public GameObject
{
	int hModel_;
public:
	Enemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

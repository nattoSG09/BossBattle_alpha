#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
	int hModel_;
	XMFLOAT3 initCamPos;
public:
	Player(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};


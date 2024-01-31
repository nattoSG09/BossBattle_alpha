#pragma once
#include "Engine/GameObject.h"
#include "FanSector.h"

class Object01 : public GameObject
{
	int hm_Point_;
	int hm_Character_;

	FanSector fan;
	XMFLOAT3 prevPos_;
public:
	Object01(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool Move();
};
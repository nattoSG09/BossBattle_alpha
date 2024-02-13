#pragma once
#include "Engine/GameObject.h"

class SkySphere : public GameObject
{
private:
	int hModel_;
public:
	SkySphere(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};


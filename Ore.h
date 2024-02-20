#pragma once
#include "Engine/GameObject.h"
#include "Circle.h"

enum {
	IRON, GOLD, DIAMOND, EMERALD, RUBY
};

class Ore : public GameObject
{
protected:
	int hModel_;
	int type_;
	Circle circle_;
public:
	Ore(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	Circle GetCircle() { return circle_; }
	int GetModelHandle() { return hModel_; }
	int GetType() { return type_; }
};


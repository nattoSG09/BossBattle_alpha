#pragma once
#include "Engine/GameObject.h"
#include "Rect.h"

class Stage : public GameObject
{
public:
	Stage(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	Rect GetExitRect() { return exitRect_; }
};


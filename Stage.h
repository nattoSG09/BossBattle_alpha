#pragma once
#include "Engine/GameObject.h"

class Stage : public GameObject
{
	int hm_Stage_view;
	int hm_Stage_collision;
public:
	Stage(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};


#pragma once
#include "Engine/GameObject.h"

class LoadScene : public GameObject
{
public:
	LoadScene(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};


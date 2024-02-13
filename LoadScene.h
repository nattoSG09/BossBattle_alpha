#pragma once
#include "Engine/GameObject.h"


class LoadScene : public GameObject
{
	int hPict_;
public:
	LoadScene(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};


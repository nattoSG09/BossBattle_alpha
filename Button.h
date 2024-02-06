#pragma once
#include "Rect.h"
#include "Engine/GameObject.h"
#include <string>

using std::string;


class Button : public GameObject
{
public:
	Rect rect_;
	int hImage_;

	Button(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void SetImage(string _filePath);
	bool Push();
};


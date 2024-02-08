#pragma once
#include "Engine/GameObject.h"
#include <map>
using std::map;
using std::string;

class State;

class Player : public GameObject
{
	int hModel_;
	map<string,State*> states_;
	State* currentState_;

public:
	Player(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void InitAllStates();
	void ChangeState(string _key);

};


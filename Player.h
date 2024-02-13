#pragma once
#include "Engine/GameObject.h"
#include <map>
using std::map;


enum STATE_HANDLE {
	S_WAIT,S_MOVE
};

class State;

class Player : public GameObject
{
	map<STATE_HANDLE, State*> states_;
	State* currentState_;
public:
	Player(GameObject* _pParent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool IsStateChange(STATE_HANDLE _hState);
	void ChangeState(STATE_HANDLE _hState);
};


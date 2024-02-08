#pragma once
#include "State.h"

class Standby : public State
{
public:
	void Initialize() override;
	void Start() override;
	void Update() override;
};


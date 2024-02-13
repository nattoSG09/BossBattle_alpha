#pragma once
#include "State.h"

class Waiting : public State
{
public:
	void Start(Player* _pPlayer) override;
	void Update(Player* _pPlayer) override;
};


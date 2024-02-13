#pragma once
#include "State.h"

class Moving : public State
{
public:
	void Start(Player* _pPlayer) override;
	void Update(Player* _pPlayer) override;
};

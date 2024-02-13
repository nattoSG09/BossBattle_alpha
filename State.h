#pragma once

class Player;

class State
{
public:
	virtual void Start(Player* _pPlayer) = 0;
	virtual void Update(Player* _pPlayer) = 0;
};


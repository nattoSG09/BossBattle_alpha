#pragma once

// ��Ԋ��N���X
class State
{
public:
	virtual void Initialize() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
};


#pragma once

// 状態基底クラス
class State
{
public:
	virtual void Initialize() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
};


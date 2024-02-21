#pragma once
#include "Engine/GameObject.h"

// �����X�^�[�̏����i�[����\����
struct MonsterInfo {
	std::string filePath;
	int speed;
	int guts;
};


class Enemy : public GameObject
{
	int hModel_;
	MonsterInfo monsterInfo_;
public:
	Enemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};


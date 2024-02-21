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
	std::map<std::string, MonsterInfo> monsters_;
public:
	Enemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};


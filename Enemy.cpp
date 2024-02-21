#include "Enemy.h"
#include "Engine/Model.h"
#include <map>
#include <fstream>
#include <sstream>

namespace {
	
    // .ini ファイルからモンスターの情報を読み込む関数
    std::map<std::string, MonsterInfo> LoadMonsterInfo(const std::string& filename) {
        std::map<std::string, MonsterInfo> monsterMap;

        std::ifstream file(filename);
        if (!file.is_open()) return monsterMap;
        
        std::string line;
        std::string currentSection;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=')) {
                if (key[0] == '[') {
                    currentSection = key.substr(1, key.size() - 2);
                    monsterMap[currentSection] = MonsterInfo();
                }
                else if (std::getline(iss, value)) {
                    if (currentSection.empty()) {
                        return monsterMap;
                    }
                    if (key == "filePath ") {
                        monsterMap[currentSection].filePath = value;
                    }
                    else if (key == "speed ") {
                        monsterMap[currentSection].speed = std::stoi(value);
                    }
                    else if (key == "guts ") {
                        monsterMap[currentSection].guts = std::stoi(value);
                    }
                }
            }
        }
        return monsterMap;
    }
}

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

void Enemy::Initialize()
{
    monsterInfo_ = LoadMonsterInfo("monsters.ini")["DiamondMutant"];

	hModel_ = Model::Load(monsterInfo_.filePath);
	Model::SetAnimFrame(hModel_, 0, 162, 1);

	transform_.rotate_.y = 180.f;
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_,transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

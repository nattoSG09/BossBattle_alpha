#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

void Enemy::Initialize()
{
	CsvReader csv;
	csv.Load("OreMonsterData.csv");

	hModel_ = Model::Load("Models/OreTyrantrolling.fbx");
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

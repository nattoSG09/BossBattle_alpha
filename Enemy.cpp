#include "Enemy.h"
#include "Engine/Model.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("")
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
}

void Enemy::Release()
{
}

#include "Enemy.h"

#include "FanSector.h"
#include "Player.h"
#include "Engine/Model.h"
#include "Engine/ImGui/imgui.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Models/OreTyrantrolling.fbx");
	Model::SetAnimFrame(hModel_, 0, 162, 1);

	transform_.position_.z += 10.f;
	speed_ = 0.05f;
}

void Enemy::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
	Chase(pPlayer);
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_,transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{

}

bool Enemy::IsChase(GameObject* _target)
{
	FanSector fan(transform_.position_.x, transform_.position_.z, 3.f, 90.f, XMFLOAT2(-1, 0));
	XMFLOAT3 tgt = _target->GetPosition();
	return fan.ContainsPoint(XMFLOAT2(tgt.x,tgt.z));
}

void Enemy::Chase(GameObject* _target)
{
	// ターゲットの位置を取得
	XMFLOAT3 target_position = _target->GetPosition();

	// 敵からターゲットに対して伸びる方向ベクトルを作成
	XMVECTOR target_To_enemy = XMLoadFloat3(&target_position) - XMLoadFloat3(&transform_.position_);
	
	// ↑の長さを取得し、その長さが一定値より小さければ追従処理は行わない
	float dist = XMVectorGetX(XMVector3Length(target_To_enemy));
	if (dist < 1.0f)return;

	// ↑のベクトルを正規化
	target_To_enemy = XMVector3Normalize(target_To_enemy);

	// １フレーム当たりの移動量を乗算し移動ベクトルを作成
	XMVECTOR move = target_To_enemy * speed_;

	// 現在の位置と移動ベクトルを加算し原点から移動後の位置に伸びるベクトルを作成
	XMVECTOR origin_To_afterPosition = XMLoadFloat3(&transform_.position_) + move;

	// ↑で作成したベクトルで座標を更新
	XMStoreFloat3(&transform_.position_, origin_To_afterPosition);
}

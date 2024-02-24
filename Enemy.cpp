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
	// �^�[�Q�b�g�̈ʒu���擾
	XMFLOAT3 target_position = _target->GetPosition();

	// �G����^�[�Q�b�g�ɑ΂��ĐL�т�����x�N�g�����쐬
	XMVECTOR target_To_enemy = XMLoadFloat3(&target_position) - XMLoadFloat3(&transform_.position_);
	
	// ���̒������擾���A���̒��������l��菬������ΒǏ]�����͍s��Ȃ�
	float dist = XMVectorGetX(XMVector3Length(target_To_enemy));
	if (dist < 1.0f)return;

	// ���̃x�N�g���𐳋K��
	target_To_enemy = XMVector3Normalize(target_To_enemy);

	// �P�t���[��������̈ړ��ʂ���Z���ړ��x�N�g�����쐬
	XMVECTOR move = target_To_enemy * speed_;

	// ���݂̈ʒu�ƈړ��x�N�g�������Z�����_����ړ���̈ʒu�ɐL�т�x�N�g�����쐬
	XMVECTOR origin_To_afterPosition = XMLoadFloat3(&transform_.position_) + move;

	// ���ō쐬�����x�N�g���ō��W���X�V
	XMStoreFloat3(&transform_.position_, origin_To_afterPosition);
}

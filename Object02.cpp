#include "Object02.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

Object02::Object02(GameObject* _pParent)
	:GameObject(_pParent,"Object02")
{
}

void Object02::Initialize()
{
	hCircle_ = Model::Load("DebugCollision/CircleCollider.fbx");
	hCharacter_ = Model::Load("Models/Character.fbx");

	transform_.position_ = { -2,0,-3 };
	transform_.rotate_.y = 90;
}

void Object02::Update()
{
	// é©êgÇÃâ~å`
	circle_.center_ = { transform_.position_.x,transform_.position_.z };
	circle_.radius_ = 1.f;

	if (Input::IsKey(DIK_W))transform_.position_.z += 0.1f;
	if (Input::IsKey(DIK_A))transform_.position_.x -= 0.1f;
	if (Input::IsKey(DIK_S))transform_.position_.z -= 0.1f;
	if (Input::IsKey(DIK_D))transform_.position_.x += 0.1f;
}

void Object02::Draw()
{
	Model::SetTransform(hCircle_, transform_);
	Model::Draw(hCircle_);

	Transform tc = transform_;
	tc.scale_ = { 2.f,2.f,2.f };

	Model::SetTransform(hCharacter_, tc);
	Model::Draw(hCharacter_);
}

void Object02::Release()
{
}

#include "Object02.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

Object02::Object02(GameObject* _pParent)
	:GameObject(_pParent,"Object02")
{
}

void Object02::Initialize()
{
	hModel_ = Model::Load("DebugCollision/CircleCollider.fbx");
}

void Object02::Update()
{
	if (Input::IsKey(DIK_W))transform_.position_.z += 0.1f;
	if (Input::IsKey(DIK_A))transform_.position_.x -= 0.1f;
	if (Input::IsKey(DIK_S))transform_.position_.z -= 0.1f;
	if (Input::IsKey(DIK_D))transform_.position_.x += 0.1f;
}

void Object02::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Object02::Release()
{
}

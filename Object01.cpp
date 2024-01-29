#include "Object01.h"
#include "Engine/Model.h"

#include "Object02.h"
#include "Circle.h"
#include "Engine/ImGui/imgui.h"

Object01::Object01(GameObject* _pParent)
	:GameObject(_pParent,"Object01")
{
}

void Object01::Initialize()
{
	hModel_ = Model::Load("DebugCollision/CircleCollider.fbx");
}

void Object01::Update()
{
	// 自身の円形情報
	circle_.center_ = { transform_.position_.x,transform_.position_.z };
	circle_.radius_ = 1.f;

	// Object02の円形情報
	Object02* pObj2 = (Object02*)FindObject("Object02");

	// 重なったら...
	if (circle_.OverlapCircle(pObj2->GetCircle())) {
		ImGui::Text("circle_.OverlapCircle = true");
	}
	else {
		ImGui::Text("circle_.OverlapCircle = false");
	}

}

void Object01::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Object01::Release()
{
}

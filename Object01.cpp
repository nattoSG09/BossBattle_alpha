#include "Object01.h"
#include "Engine/Model.h"

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
	ImGui::Text("aaa");
}

void Object01::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Object01::Release()
{
}

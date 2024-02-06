#include "TestScene.h"

#include "Rect.h"
#include "Engine/Input.h"
#include "Engine/ImGui/imgui.h"
#include "Button.h"

TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{	
	pButton_ = Instantiate<Button>(this);
}

void TestScene::Update()
{
	XMFLOAT3 mPos = Input::GetMousePosition();
	ImGui::Text("mousePos = %f,%f", mPos.x, mPos.y);

	ImGui::Text("ButtonPos = %f,%f", pButton_->rect_.center_.x, pButton_->rect_.center_.y);
	ImGui::Text("ButtonSize = w%f,h%f", pButton_->rect_.width_, pButton_->rect_.height_);

	if (pButton_->Push()) {
		ImGui::Text("Push = true");
	}
	else {
		ImGui::Text("Push = false");
	}
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}

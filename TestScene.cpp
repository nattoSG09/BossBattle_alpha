#include "TestScene.h"

#include "Rect.h"
#include "Engine/Input.h"
#include "Engine/ImGui/imgui.h"

TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{	
}

void TestScene::Update()
{
	XMFLOAT3 mPos = Input::GetMousePosition();
	ImGui::Text("mousePos = %f,%f", mPos.x, mPos.y);

	Rect rect(640.f, 360.f, 100.f, 150.f);
	
	if (rect.ContainsPoint(mPos.x, mPos.y)) {
		ImGui::Text("rect.ContainsPoint = true");
	}
	else {
		ImGui::Text("rect.ContainsPoint = false");
	}

}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}

#include "TestScene.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/Camera.h"

#include "Object01.h"
#include "Object02.h"

TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(0,5,-10));
	Instantiate<Object01>(this);
	Instantiate<Object02>(this);
}

void TestScene::Update()
{
	XMFLOAT3 playerPos = player_->GetPosition();
	if (pStage_->GetExitRect().ContainsPoint(playerPos.x, playerPos.z)) {
		ImGui::Text("exit ok");
		((SceneManager*)FindObject("SceneManager"))->ChangeScene(SCENE_ID_LOAD, TID_BLACKOUT, 1.f);

	}

}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}

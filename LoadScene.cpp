#include "LoadScene.h"
#include "Engine/SceneManager.h"
#include "Engine/ImGui/imgui.h"

LoadScene::LoadScene(GameObject* _pParent)
	:GameObject(_pParent,"LoadScene")
{
}

void LoadScene::Initialize()
{
}

void LoadScene::Update()
{
	//if (ImGui::Button("SceneChange")) {
	((SceneManager*)FindObject("SceneManager"))->ChangeScene(SCENE_ID_TEST, TID_BLACKOUT, 2.f);
	//}
}

void LoadScene::Draw()
{
}

void LoadScene::Release()
{
}

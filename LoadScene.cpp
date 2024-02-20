#include "LoadScene.h"
#include "Engine/SceneManager.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/Image.h"

LoadScene::LoadScene(GameObject* _pParent)
	:GameObject(_pParent,"LoadScene")
{
}

void LoadScene::Initialize()
{
	hPict_ = Image::Load("Miner'sHope_Images/title_color01.png");
	transform_.scale_ = { 0.5f,0.5f ,0.5f };
}

void LoadScene::Update()
{
	static int time = 0;
	time += 1.f;
	if (time >= 3*60.f) {
	((SceneManager*)FindObject("SceneManager"))->ChangeScene(SCENE_ID_TEST, TID_BLACKOUT, 2.f);
	}
}

void LoadScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void LoadScene::Release()
{
}

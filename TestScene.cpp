#include "TestScene.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/Camera.h"

#include<iostream>
#include "Stage.h"
#include "Player.h"
#include "OreManager.h"
#include "SkySphere.h"
#include "Engine/SceneManager.h"

TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{	

	// ��肽���Q�[���E�E�E�Ȃ�

	// �����̏�����
	srand((unsigned int)time(nullptr));

	// �K�v��GameObject
	{
		// �v���C���[
		player_ = Instantiate<Player>(this);

		// �z��
		for(int i=0;i<10;i++)
		OreManager::CreateOre<Ore>(XMFLOAT3((rand() % 7 - 4) * 5, 0, (rand() % 7 - 4)* 5), this);
		
		// �X�e�[�W
		pStage_ = Instantiate<Stage>(this);

		// ��
		Instantiate<SkySphere>(this);
	}

	// �J�����̐ݒ�
	Camera::SetPosition(XMFLOAT3(0, 10, -30));
	Camera::SetTarget(XMFLOAT3(0, 7, 0));
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
	OreManager::AllRelease();
}

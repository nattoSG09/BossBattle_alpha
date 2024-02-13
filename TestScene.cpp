#include "TestScene.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/Camera.h"

#include<iostream>
#include "Stage.h"
#include "Player.h"
#include "Ore.h"
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
		for (int i = 0; i < 3; i++) {
			Ore* ore = Instantiate<Ore>(this);
			ore->SetPosition(rand() % 20 + 1, 0, rand() % 20 + 1);
		}


		// �X�e�[�W
		Instantiate<Stage>(this);

		// ��
		Instantiate<SkySphere>(this);
	}

	// �J�����̐ݒ�
	Camera::SetPosition(XMFLOAT3(0, 10, -20));
	Camera::SetTarget(XMFLOAT3(0, 7, 0));
}

void TestScene::Update()
{
	if (player_->GetPosition().z >= 25.f) {
		((SceneManager*)FindObject("SceneManager"))->ChangeScene(SCENE_ID_LOAD, TID_BLACKOUT, 1.f);
	}

	Camera::SetTarget(player_->GetPosition());

}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}

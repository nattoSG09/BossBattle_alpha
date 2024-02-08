#include "TestScene.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/Camera.h"

#include "Stage.h"
#include "Player.h"

TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{	
	// �J�����̐ݒ�
	Camera::SetPosition(XMFLOAT3(0, 10, -20));
	Camera::SetTarget(XMFLOAT3(0, 7, 0));
	// ��肽���Q�[���E�E�E�Ȃ�

	// �K�v��GameObject
	{
		// �v���C���[
		Instantiate<Player>(this);

		// �z��


		// �X�e�[�W
		Instantiate<Stage>(this);
	}
}

void TestScene::Update()
{

}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}

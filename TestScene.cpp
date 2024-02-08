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
	// カメラの設定
	Camera::SetPosition(XMFLOAT3(0, 10, -20));
	Camera::SetTarget(XMFLOAT3(0, 7, 0));
	// 作りたいゲーム・・・ない

	// 必要なGameObject
	{
		// プレイヤー
		Instantiate<Player>(this);

		// 鉱石


		// ステージ
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

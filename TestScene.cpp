#include "TestScene.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/Camera.h"
#include<iostream>
#include "Stage.h"
#include "Player.h"
#include "Ore.h"

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

	// 乱数の初期化
	srand((unsigned int)time(nullptr));

	// 必要なGameObject
	{
		// プレイヤー
		Instantiate<Player>(this);

		// 鉱石
		for (int i = 0; i < 3; i++) {
			Ore* ore = Instantiate<Ore>(this);
			ore->SetPosition(rand() % 20 + 1, 0, rand() % 20 + 1);
		}

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

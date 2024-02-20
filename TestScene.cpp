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

	// 作りたいゲーム・・・ない

	// 乱数の初期化
	srand((unsigned int)time(nullptr));

	// 必要なGameObject
	{
		// プレイヤー
		player_ = Instantiate<Player>(this);

		// 鉱石

		// ステージ
		pStage_ = Instantiate<Stage>(this);

		// 空
		Instantiate<SkySphere>(this);
	}

	// カメラの設定
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
}

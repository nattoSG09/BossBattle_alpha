#include "TestScene.h"

#include "Engine/Camera.h"

#include "Object01.h"
#include "Object02.h"
#include "Stage.h"

TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{
	Camera::SetPosition(XMFLOAT3(0,5,-10));
	Instantiate<Object01>(this);
	Instantiate<Object02>(this);
	Instantiate<Stage>(this);
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

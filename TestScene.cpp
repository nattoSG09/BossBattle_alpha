#include "TestScene.h"

#include "Rect.h"
#include "Engine/Input.h"

TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{
	XMFLOAT3 mPos = Input::GetMousePosition();

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

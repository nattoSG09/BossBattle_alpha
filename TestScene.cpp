#include "TestScene.h"

#include "Object01.h"
#include "Object02.h"

TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{
	Instantiate<Object01>(this);
	Instantiate<Object02>(this);
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

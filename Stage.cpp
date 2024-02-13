#include "Stage.h"
#include "Engine/Model.h"

Stage::Stage(GameObject* _pParent)
	:GameObject(_pParent,"Stage")
{
}

void Stage::Initialize()
{
	hModel_ = Model::Load("Models/forest_ground_02.fbx");
	transform_.rotate_.y = 180.f;
	//transform_.scale_ = { 2.f,2.f,2.f };
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Stage::Release()
{
}

#include "Stage.h"
#include "Engine/Model.h"

Stage::Stage(GameObject* _parent)
	:GameObject(_parent,"Stage")
{
}

void Stage::Initialize()
{
	hModel_ = Model::Load("Models/stage_debug.fbx");
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

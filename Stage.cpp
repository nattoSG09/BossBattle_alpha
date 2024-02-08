#include "Stage.h"
#include "Engine/Model.h"

Stage::Stage(GameObject* _pParent)
	:GameObject(_pParent,"Stage")
{
}

void Stage::Initialize()
{
	hModel_ = Model::Load("Models/leafy_grass_stage.fbx");
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

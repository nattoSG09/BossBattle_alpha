#include "Stage.h"
#include "Engine/Model.h"

Stage::Stage(GameObject* _pParent)
	:GameObject(_pParent,"Stage")
{
}

void Stage::Initialize()
{
	// ƒ‚ƒfƒ‹‚Ì“Ç‚İ‚İˆ—
	{
		hm_Stage_view = Model::Load("Models/Stage_View.fbx");
		hm_Stage_collision = Model::Load("Models/Stage_View.fbx");
	}

	transform_.scale_ = { 5.0f,3.0f,3.0f };
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Model::SetTransform(hm_Stage_view, transform_);
	Model::Draw(hm_Stage_view);

	Model::SetTransform(hm_Stage_collision, transform_);
	Model::Draw(hm_Stage_collision);
}

void Stage::Release()
{
}

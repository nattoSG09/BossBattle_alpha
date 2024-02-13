#include "SkySphere.h"
#include "Engine/Model.h"

SkySphere::SkySphere(GameObject* _pParent)
	:GameObject(_pParent,"SkySphere")
{
}

void SkySphere::Initialize()
{
	hModel_ = Model::Load("Models/SkySphere.fbx");
}

void SkySphere::Update()
{
}

void SkySphere::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void SkySphere::Release()
{
}

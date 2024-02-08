#include "DiamondOre.h"
#include "Engine/Model.h"

DiamondOre::DiamondOre(GameObject* _pParent)
	:GameObject(_pParent,"DiamondOre")
{
}

void DiamondOre::Initialize()
{
	hModel_ = Model::Load("Models/diamond_ore.fbx");
	transform_.scale_ = { 2.f,2.f, 2.f };
	transform_.rotate_.y = 90;
	transform_.position_ = { 2.f,0.f,5.f };
}

void DiamondOre::Update()
{
}

void DiamondOre::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void DiamondOre::Release()
{
}

#include "Ore.h"
#include "Engine/Model.h"
#include "Engine/ImGui/imgui.h"
#include "Player.h"

Ore::Ore(GameObject* _pParent)
	:GameObject(_pParent,"Ore")
{
}

void Ore::Initialize()
{
	hModel_ = Model::Load("Models/ore_diamond.fbx");
	transform_.scale_ = { 2.f,2.f, 2.f };
	transform_.rotate_.y = 90;
}

void Ore::Update()
{
	//ÉTÅ[ÉNÉãèÓïÒÇÃê›íË
	circle_.center_ = { transform_.position_.x,transform_.position_.z };
	circle_.radius_ = 4.f;

	//ImGui::Text("Ore Circle center = { x %f,z %f }", circle_.center_.x, circle_.center_.y);
	//ImGui::Text("Ore Circle radius = %f", circle_.radius_);
	//ImGui::Text("Ore Position = { x %f,y %f,z %f", transform_.position_.x, transform_.position_.y, transform_.position_.z);
}

void Ore::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Ore::Release()
{
}

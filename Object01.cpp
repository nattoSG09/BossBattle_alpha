#include "Object01.h"
#include "Engine/Model.h"

#include "Object02.h"
#include "Engine/ImGui/imgui.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"

namespace {
	XMVECTOR CreateXMVECTORFromXMFLOAT2(const XMFLOAT2& _point1, const XMFLOAT2& _point2) {
		return XMVectorSet(_point2.x - _point1.x, _point2.y - _point1.y, 0.0f, 0.0f);
	}

	XMVECTOR CreateXMVECTORFromXMFLOAT3(const XMFLOAT3& _point1, const XMFLOAT3& _point2) {
		return XMVectorSet(_point2.x - _point1.x, _point2.y - _point1.y,_point2.z - _point1.z, 0.0f);
	}
}


Object01::Object01(GameObject* _pParent)
	:GameObject(_pParent,"Object01"),fan(transform_.position_.x,transform_.position_.z,1,90,XMFLOAT2(1,0))
{
}

void Object01::Initialize()
{
	hm_Point_ = Model::Load("DebugCollision/Point.fbx");
	hm_Character_ = Model::Load("DebugCollision/BoxCollider.fbx");

}

void Object01::Update()
{
	fan.center_ = { transform_.position_.x,transform_.position_.z };

	// 扇の方向ベクトルを設定
	{
		// 進行方向ベクトルの取得
		// ※現在の位置　から　前フレームの位置　を引いたベクトル
		XMVECTOR travelDir = XMVector3Normalize(CreateXMVECTORFromXMFLOAT3(prevPos_,transform_.position_));

		fan.direction_ = XMFLOAT2(/*進行方向ベクトル*/XMVectorGetX(travelDir), XMVectorGetZ(travelDir));
		
		// 移動キーが押されている間のみprevPositionを更新する
		if(Input::IsKey(DIK_W) || Input::IsKey(DIK_A) || Input::IsKey(DIK_S) || Input::IsKey(DIK_D))prevPos_ = transform_.position_;
	}

	auto o2Pos = ((Object02*)FindObject("Object02"))->GetPosition();
	ImGui::Text("object02 Position = %f,%f", o2Pos.x, o2Pos.z);
	ImGui::Text("object01 Position = %f,%f", transform_.position_.x, transform_.position_.z);

	if (fan.ContainsPoint(XMFLOAT2(o2Pos.x, o2Pos.z))) {
		ImGui::Text("fan.ContainsPoint = true");
	}
	else {
		ImGui::Text("fan.ContainsPoint = false");
	}

	// 移動
	if (Input::IsKey(DIK_W)) transform_.position_.z += 0.1f;
	if (Input::IsKey(DIK_A))transform_.position_.x -= 0.1f;
	if (Input::IsKey(DIK_S))transform_.position_.z -= 0.1f;
	if (Input::IsKey(DIK_D))transform_.position_.x += 0.1f;
}

void Object01::Draw()
{

	Direct3D::SetShader(Direct3D::SHADER_UNLIT);
	Model::SetTransform(hm_Character_, transform_);
	Model::Draw(hm_Character_);

	Transform tp = transform_; {
		tp.position_.y = -0.5f;
	}

	Direct3D::SetShader(Direct3D::SHADER_3D);
	Model::SetTransform(hm_Point_, tp);
	Model::Draw(hm_Point_);
}

void Object01::Release()
{
}

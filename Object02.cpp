#include "Object02.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Direct3D.h"

Object02::Object02(GameObject* _pParent)
	:GameObject(_pParent,"Object02")
{
}

void Object02::Initialize()
{
	hm_Point_ = Model::Load("DebugCollision/Point.fbx");
}

void Object02::Update()
{
	
}

void Object02::Draw()
{
	Transform tp = transform_; {
		tp.position_.y = -0.5f;
	}

	Direct3D::SetShader(Direct3D::SHADER_3D);
	Model::SetTransform(hm_Point_, tp);
	Model::Draw(hm_Point_);
}

void Object02::Release()
{
}

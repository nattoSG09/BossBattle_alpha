#include "Button.h"
#include "Engine/Image.h"
#include "Engine/Input.h"

Button::Button(GameObject* _pParent)
	:GameObject(_pParent,"Button")
{
}

void Button::Initialize()
{
	hImage_ = Image::Load("CommonButtonBack.png");
}

void Button::Update()
{
	rect_.center_ = { transform_.position_.x + (1280/2),transform_.position_.y + (720/2)};
	rect_.width_ = Image::GetSize(hImage_).x;
	rect_.height_ = Image::GetSize(hImage_).y;
}

void Button::Draw()
{
	Image::SetTransform(hImage_, transform_);
	Image::Draw(hImage_);
}

void Button::Release()
{
}

void Button::SetImage(string _filePath)
{
	hImage_ = Image::Load(_filePath);
}

bool Button::Push()
{
	XMFLOAT2 mousePos = { Input::GetMousePosition().x,Input::GetMousePosition().y };
	return rect_.ContainsPoint(mousePos) && Input::IsMouseButton(0);
}

#include "Button.h"
#include "Engine/Image.h"

Button::Button(GameObject* _pParent)
	:GameObject(_pParent,"Button")
{
}

void Button::Initialize()
{
}

void Button::Update()
{
	rect_.center_ = { transform_.position_.x,transform_.position_.y };
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

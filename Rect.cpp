#include "Rect.h"

Rect::Rect(float _cx, float _cy, float _width, float _height)
	:Rect(XMFLOAT2(_cx,_cy),_width,_height)
{
}

Rect::Rect(XMFLOAT2 _center, float _width, float _height)
	:center_(_center),width_(_width),height_(_height)
{
}

bool Rect::ContainsPoint(float _px, float _py)
{
	return ContainsPoint(XMFLOAT2(_px,_py));
}

bool Rect::ContainsPoint(XMFLOAT2 _point)
{
	return false;
}

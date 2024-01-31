#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class FanSector
{
public:
    XMFLOAT2 center_;       // 中心座標
    float length_;          // 扇の長さ
    float angle_;           // 扇の範囲（角度）（ディグリー）
    XMFLOAT2 direction_;    // 方向（角度）（単位ベクトル）
    FanSector(float _cX, float _cY, float _length, float _angle, XMFLOAT2 _direction);

    bool ContainsPoint(const XMFLOAT2 _point);

    XMFLOAT2 GetEndpoint1();
    XMFLOAT2 GetEndpoint2();
};


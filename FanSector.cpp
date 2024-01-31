#include "FanSector.h"

namespace {
    XMVECTOR CreateXMVECTORFromXMFLOAT2(const XMFLOAT2& _point1, const XMFLOAT2& _point2) {
        return XMVectorSet(_point2.x - _point1.x, _point2.y - _point1.y, 0.0f, 0.0f);
    }
}

FanSector::FanSector(float _cX, float _cY, float _length, float _angle,XMFLOAT2 _direction)
	:center_(_cX, _cY), length_(_length), angle_(_angle), direction_(_direction)

{
}

bool FanSector::ContainsPoint(const XMFLOAT2 _point)
{
    // 扇と点のベクトルを求める
    XMVECTOR distance = CreateXMVECTORFromXMFLOAT2(center_, _point);


    // ↑の長さを求める
    float distanceLength = XMVectorGetX(XMVector2LengthSq(distance));


    // 長さを比較する
    // ※(満たされていない場合は、ここで判定を終了)
    if (!(distanceLength < length_ * length_))return false;

    // 方向ベクトルを作成
    XMVECTOR vecDirection = XMLoadFloat2(&direction_);

    // 「扇の方向ベクトル」と「扇と点のベクトル」の内積を求める
    float dot = XMVectorGetX(XMVector2Dot(vecDirection, XMVector2Normalize(distance)));


    // 扇の範囲からcosの値を求める
    float angleCos = cos(XMConvertToRadians(angle_ / 2.0f));


    return angleCos <= dot;
}

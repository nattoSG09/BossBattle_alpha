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
    // ��Ɠ_�̃x�N�g�������߂�
    XMVECTOR distance = CreateXMVECTORFromXMFLOAT2(center_, _point);


    // ���̒��������߂�
    float distanceLength = XMVectorGetX(XMVector2LengthSq(distance));


    // �������r����
    // ��(��������Ă��Ȃ��ꍇ�́A�����Ŕ�����I��)
    if (!(distanceLength < length_ * length_))return false;

    // �����x�N�g�����쐬
    XMVECTOR vecDirection = XMLoadFloat2(&direction_);

    // �u��̕����x�N�g���v�Ɓu��Ɠ_�̃x�N�g���v�̓��ς����߂�
    float dot = XMVectorGetX(XMVector2Dot(vecDirection, XMVector2Normalize(distance)));


    // ��͈̔͂���cos�̒l�����߂�
    float angleCos = cos(XMConvertToRadians(angle_ / 2.0f));


    return angleCos <= dot;
}

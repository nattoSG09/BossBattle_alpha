#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class FanSector
{
public:
    XMFLOAT2 center_;       // ���S���W
    float length_;          // ��̒���
    float angle_;           // ��͈̔́i�p�x�j�i�f�B�O���[�j
    XMFLOAT2 direction_;    // �����i�p�x�j�i�P�ʃx�N�g���j
    FanSector(float _cX, float _cY, float _length, float _angle, XMFLOAT2 _direction);

    bool ContainsPoint(const XMFLOAT2 _point);

    XMFLOAT2 GetEndpoint1();
    XMFLOAT2 GetEndpoint2();
};


#pragma once
#include <DirectXMath.h>
#include "Ore.h"

#include <vector>
using namespace std;


#include "Engine/GameObject.h"
using namespace DirectX;

namespace OreManager
{
	extern vector<Ore*> ores_;

	template<class T>
	void CreateOre(XMFLOAT3 _position, GameObject* parent) {
		T* ore = Instantiate<T>(parent);
		ore->SetPosition(_position);
		ores_.push_back(ore);
	}

	void Destroy(Ore* _ore);
};

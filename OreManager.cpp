#include "OreManager.h"
#include "Engine/Global.h"

vector<Ore*> OreManager::ores_;

void OreManager::Destroy(Ore* _ore)
{
	auto it = std::find(ores_.begin(), ores_.end(), _ore);
	_ore->KillMe();
	ores_.erase(it);
}

void OreManager::AllRelease()
{
	ores_.clear(); // ores_‚ð‹ó‚É‚·‚é
}

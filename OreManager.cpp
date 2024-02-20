#include "OreManager.h"

vector<Ore*> OreManager::ores_;

void OreManager::Destroy(Ore* _ore)
{
	auto it = std::find(ores_.begin(), ores_.end(), _ore);
	_ore->KillMe();
	ores_.erase(it);
}
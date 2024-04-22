// attorney class for terrain manager

#ifndef _TerrainManagerAttorney
#define _TerrainManagerAttorney

#include "TerrainManager.h"

class TerrainManagerAttorney
{
	friend class Game;

private:
	static void Terminate() { TerrainManager::Instance().privDelete(); };
};

#endif _TerrainManagerAttorney
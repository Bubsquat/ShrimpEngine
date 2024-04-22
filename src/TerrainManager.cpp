// singleton asset manager for engine terrain objects 

#include "TerrainManager.h"
#include "HeightmapTerrain.h"

TerrainManager* TerrainManager::ptrInstance = nullptr;

void TerrainManager::privDelete()
{
	// delete map elements
	for (TerrainMap::iterator it = terrainMap.begin(); it != terrainMap.end(); ++it)
	{
		delete it->second;
	}
	terrainMap.clear();

	// delete 
	delete ptrInstance;
	ptrInstance = nullptr;
}

void TerrainManager::privLoad(TerrainMap::key_type key, const char* heightmapFilename, Vect centerPoint, float sideLength, float maxHeight, Texture* texture, float yOffset, int uRepeat, int vRepeat)
{
	HeightmapTerrain* newTerrain = new HeightmapTerrain(heightmapFilename, centerPoint, sideLength, maxHeight, texture , yOffset, uRepeat, vRepeat);

	std::pair<const std::string, HeightmapTerrain*> newItem = { key, newTerrain };
	terrainMap.emplace(newItem);

}

HeightmapTerrain* TerrainManager::privGet(TerrainMap::key_type key)
{
	assert(terrainMap.find(key) != terrainMap.end());
	return terrainMap.find(key)->second;
}
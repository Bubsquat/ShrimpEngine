// singleton asset manager for engine terrain objects 

#ifndef _TerrainManager
#define _TerrainManager

#include "AzulCore.h"
#include <map>

class HeightmapTerrain;

class TerrainManager
{
private:

	static TerrainManager* ptrInstance;

	using TerrainMap = std::map<const std::string, HeightmapTerrain*>;
	TerrainMap terrainMap;

	TerrainManager() = default;
	TerrainManager(const TerrainManager&) = delete;
	TerrainManager& operator=(const TerrainManager&) = delete;
	~TerrainManager() = default;

	static TerrainManager& Instance()
	{
		if (!ptrInstance)
		{
			ptrInstance = new TerrainManager();
		}
		return *ptrInstance;
	}

	void privDelete();
	void privLoad(TerrainMap::key_type key, const char* heightmapFilename, Vect centerPoint, float sideLength, float maxHeight, Texture* texture, float yOffset, int uRepeat, int vRepeat);
	HeightmapTerrain* privGet(TerrainMap::key_type key);

	friend class TerrainManagerAttorney;

public:

	static void Load(TerrainMap::key_type key, const char* heightmapFilename, Vect centerPoint, float sideLength, float maxHeight, Texture* texture ,float yOffset = 0.0, int uRepeat = 0, int vRepeat = 0) {
		Instance().privLoad(key, heightmapFilename, centerPoint, sideLength, maxHeight, texture ,yOffset, uRepeat, vRepeat); };

	static HeightmapTerrain* Get(TerrainMap::key_type key) { return Instance().privGet(key); };
};

#endif _TerrainManager

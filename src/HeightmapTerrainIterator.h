// iterator for Heightmap Terrain  

#ifndef _HeightmapTerrainIterator
#define _HeightmapTerrainIterator

#include "HeightmapTerrain.h"

class CollisionVolumeBSphere;

class HeightmapTerrainIterator
{
public:

	HeightmapTerrainIterator() = default;
	//HeightmapTerrainIterator(HeightmapTerrain* hmTerrain, const CollisionVolumeBSphere& bs);
	HeightmapTerrainIterator(const HeightmapTerrainIterator&) = delete; 
	HeightmapTerrainIterator& operator=(const HeightmapTerrainIterator&) = delete; // might be some use in defining these later
	~HeightmapTerrainIterator() = default;

	// prefix inc and dec operators 
	HeightmapTerrainIterator& operator++();
	HeightmapTerrainIterator& operator--();
	//HeightmapTerrainIterator operator++(int);
	//HeightmapTerrainIterator operator--(int)

 
	void SetCell(int x, int z);
	void SetBSphere(const CollisionVolumeBSphere& bs);
	void SetTerrain(HeightmapTerrain* pt);
	const HeightmapTerrain::cellData& GetCell();
	const HeightmapTerrain::cellData& GetBegin();
	const HeightmapTerrain::cellData& GetEnd();

private:

	int beginX;
	int beginZ;
	int endX;
	int endZ;
	int curX;
	int curZ;
	HeightmapTerrain* terrain;
	HeightmapTerrain::cellData curCell;

};

#endif _HeightmapTerrainIterator

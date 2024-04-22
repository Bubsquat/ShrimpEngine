// terrain model from heightmap

#ifndef _HeightmapTerrain
#define _HeightmapTerrain 

#include "AzulCore.h"
#include "GpuVertTypes.h"
#include <list>
#include "Drawable.h"

// not sure terrain should be a game object or not
// for now its gunna have a getter method for the model   

class CollisionVolumeAABB;
class CollisionVolumeBSphere;
class HeightmapTerrainIterator;

class HeightmapTerrain : public Drawable
{
public :

	HeightmapTerrain() = delete;
	HeightmapTerrain(const char* heightmapFilename, Vect centerPoint, float sideLength, float maxHeight, Texture* texture, float yOffset, int uRepeat, int vRepeat);
	HeightmapTerrain(const HeightmapTerrain&) = delete;
	HeightmapTerrain& operator= (const HeightmapTerrain&) = delete;
	~HeightmapTerrain();

	void Draw();
	void TestDraw();

	Model* GetTerrainModel();
	GraphicsObject_WireframeConstantColor* pTestGo;
	GraphicsObject_TextureFlat* pGoTerrain;

	struct cellData
	{
		int cellX;
		int cellZ;
		Vect Min;
		Vect Max;
	};

	using CollisionInfoList = std::list<cellData>;
	CollisionInfoList colInfoList;

	const std::list<cellData>& GetTerrainCollisionInfo() const;
	const cellData& GetTerrainCell(const Vect& position);
	const cellData& GetTerrainCell(int x, int z);
	Vect GetNormal(const Vect& position);
	Vect GetTerrainPoint(const Vect& position);
	void GetBSphereCells(const CollisionVolumeBSphere& bs, int& xMin, int& zMin, int& xMax, int& zMax);
	int GetCellsPerSide();
	HeightmapTerrainIterator* GetIterator();

private:

	const char* textLoc = "Textures\\";
	Model* terrainModel;

	Vect terrainCenterpoint;
	float terrainSideLength;
	float cellSize;
	int cellsPerSide;
	int imgWidth;

	HeightmapTerrainIterator* iterator;

	Vect getPointNorm(int pointX, int pointZ);

};

#endif _Terrain

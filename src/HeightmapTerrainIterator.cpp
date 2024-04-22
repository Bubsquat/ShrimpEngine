// iterator for Heightmap Terrain  

#include "HeightmapTerrainIterator.h"
#include <assert.h>
#include "CollisionVolumeBSphere.h"
#include "SceneManager.h"

//HeightmapTerrainIterator::HeightmapTerrainIterator(HeightmapTerrain* _pt, const CollisionVolumeBSphere& bs)
//{
//	terrain = _pt;
//	terrain->GetBSphereCells(bs, beginX, beginZ, endX, endZ);
//	curX = beginX;
//	curZ = beginZ;
//	curCell = terrain->GetTerrainCell(beginX, beginZ);
//}

//HeightmapTerrainIterator::HeightmapTerrainIterator()
//{
//	SetTerrain(SceneManager::GetCurrentScene()->GetTerrain());
//}

HeightmapTerrainIterator& HeightmapTerrainIterator::operator++()
{

	if (curX + 1 > endX || curX + 1 > terrain->GetCellsPerSide() - 1)
	{
		curX = beginX;
		if (curZ == endZ || curZ == terrain->GetCellsPerSide() - 1) assert("End of range");
		else curZ++;
	}
	else
	{
		curX++;
	}
	
	curCell = terrain->GetTerrainCell(curX, curZ);
	return *this;
}

HeightmapTerrainIterator& HeightmapTerrainIterator::operator--()
{

	if (curX - 1 < beginX || curX - 1 < 0)
	{
		curX = endX;
		if (curZ == beginZ || curZ == 0) assert("Beginning of range");
		else curZ--;
	}
	else
	{
		curX--;
	}

	curCell = terrain->GetTerrainCell(curX, curZ);
	return *this;
}

void HeightmapTerrainIterator::SetTerrain(HeightmapTerrain* pt)
{
	this->terrain = pt;
	//beginX = 0;
	//beginZ = 0;
	//endX = terrain->GetCellsPerSide() - 1;
	//endZ = terrain->GetCellsPerSide() - 1;
	//curX = beginX;
	//curZ = beginZ;
	//curCell = terrain->GetTerrainCell(beginX, beginZ);
}

void HeightmapTerrainIterator::SetBSphere(const CollisionVolumeBSphere& bs)
{
	terrain->GetBSphereCells(bs, beginX, beginZ, endX, endZ);
	curX = beginX;
	curZ = beginZ;
	curCell = terrain->GetTerrainCell(beginX, beginZ);
}

void HeightmapTerrainIterator::SetCell(int x, int z)
{
	if (x <= endX && x >= beginX) curX = x;
	if (z <= endZ && z >= beginZ) curZ = z;
	curCell = terrain->GetTerrainCell(curX, curZ);
}

const HeightmapTerrain::cellData& HeightmapTerrainIterator::GetCell()
{
	return curCell;
}

const HeightmapTerrain::cellData& HeightmapTerrainIterator::GetBegin()
{
	return terrain->GetTerrainCell(beginX, beginZ);
}

const HeightmapTerrain::cellData& HeightmapTerrainIterator::GetEnd()
{
	return terrain->GetTerrainCell(endX, endZ);
}
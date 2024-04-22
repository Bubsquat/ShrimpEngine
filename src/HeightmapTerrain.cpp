// terrain model from heightmap

#include "HeightmapTerrain.h"
#include "TextureTGA.h"
#include <assert.h>
#include "SMathTools.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "CameraManager.h"
#include "HeightmapTerrainIterator.h"

#include "DataLogger.h"
#include "Visualizer.h"

HeightmapTerrain::HeightmapTerrain(const char* heightmapFilename, Vect centerPoint, float sideLength, float maxHeight, Texture* texture, float yOffset, int uRepeat, int vRepeat)
{	

	this->terrainCenterpoint = centerPoint;
	this->terrainSideLength = sideLength;

	// get heightmap info  

	int imgHeight, icomp;
	unsigned int dtype;
	std::string filePath = std::string(heightmapFilename);
	filePath = std::string(textLoc) + filePath;
	GLbyte* imgData = gltReadTGABits(filePath.c_str(), &imgWidth, &imgHeight, &icomp, &dtype);
	assert(imgWidth == imgHeight && imgWidth != 0); // verify the img is square

	int NUM_VERTS = imgWidth * imgHeight;
	int NUM_TRIS = 2 * (imgWidth - 1) * (imgHeight - 1);

	// generate model 

	VertexStride_VUN* pVerts = new VertexStride_VUN[NUM_VERTS];
	TriangleIndex* tlist = new TriangleIndex[NUM_TRIS];

	// verts

	float posOffset = sideLength / imgHeight;
	posOffset += posOffset / imgHeight;
	this->cellSize = posOffset;
	int curVert = 0;
	float heightStep = maxHeight / 255.0f;

	float uStep = uRepeat / static_cast<float>(imgWidth);
	float vStep = vRepeat / static_cast<float>(imgHeight);

	for (int z = 0; z < imgHeight; z++)
	{
		for (int x = 0; x < imgWidth; x++)
		{

			// get height value 
			int index = (x * 3) + ((z * imgWidth) * 3);
			GLbyte pixInfo = imgData[index];
			unsigned char pix = static_cast<unsigned char>(pixInfo);
			float heightVal = static_cast<float>(pix) * heightStep;
			heightVal += yOffset;

			// get vert location 
			float posX = (x * -posOffset) + (sideLength / 2.0f);
			float posZ = (z * -posOffset) + (sideLength / 2.0f);

			// calculate uvs 
			float u = uStep * x;
			float v = vStep * z;

			// set vert
			pVerts[curVert].set(posX, heightVal, posZ,u,v, 0.0f,0.0f,0.0f);
			curVert++;

		}

	}

	// calculate normals 
	//curVert = 0;
	//for (int z = 0; z < imgHeight; z++)
	//{
	//	for (int x = 0; x < imgWidth; x++)
	//	{

	//		Vect vertNormal;

	//		if ((x == 0 || x == imgWidth - 1) && (z == imgHeight - 1)) // edge cases 
	//		{
	//			vertNormal = Vect(0.0f, 1.0f, 0.0f, 0.0f);
	//		}
	//		else // calculate actual normal
	//		{

	//			// get the points to the right and above

	//			Vect aboveVect;
	//			int aboveLoc = x + ((z + 1) * (imgWidth - 1));
	//			aboveVect.set(Vect(pVerts[aboveLoc].x, pVerts[aboveLoc].y, pVerts[aboveLoc].z));

	//			Vect leftVect;
	//			int leftLoc = curVert + 1;
	//			leftVect.set(Vect(pVerts[leftLoc].x, pVerts[leftLoc].y, pVerts[leftLoc].z));
	//			
	//			// get their cross product 

	//			vertNormal = aboveVect.cross(leftVect);
	//			vertNormal = vertNormal.getNorm();

	//		}

	//		pVerts[curVert].nx = vertNormal.X();
	//		pVerts[curVert].ny = vertNormal.Y();
	//		pVerts[curVert].nz = vertNormal.Z();

	//		curVert++;
	//	}
	//}

	// tris 

	int triNum = 0;

	for (int z = 0; z < imgHeight - 1; z++)
	{
		for (int x = 0; x < imgWidth - 1; x++)
		{

			tlist[triNum].set(x + (imgWidth * z), x + (imgWidth * (z + 1)), x + (imgWidth * z) + 1);
			triNum++;
			tlist[triNum].set(x + (imgWidth * (z + 1)), x + (imgWidth * (z + 1)) + 1, x + (imgWidth * z) + 1);
			triNum++;

		}
	}

	// generate terrain collision info 

	int totalCellNum = NUM_TRIS / 2;
	cellsPerSide = static_cast<int>(sqrtf(static_cast<float>(totalCellNum))); // slow calc but only done once per construction of a terrain 

	for (int z = 0; z < cellsPerSide; z++)
	{

		for (int x = 0; x < cellsPerSide; x++)
		{

			// get cell indexes 
			int bottomLeftIndex = x + (z * (cellsPerSide + 1));
			int bottomRightIndex = x + 1 + (z * (cellsPerSide + 1));
			int topLeftIndex = x + ((z + 1) * (cellsPerSide + 1));
			int topRightIndex = x + 1 + ((z + 1) * (cellsPerSide + 1));

			// get cell vectors 
			Vect bottomLeft = Vect(pVerts[bottomLeftIndex].x, pVerts[bottomLeftIndex].y, pVerts[bottomLeftIndex].z);
			Vect bottomRight = Vect(pVerts[bottomRightIndex].x, pVerts[bottomRightIndex].y, pVerts[bottomRightIndex].z);
			Vect topLeft = Vect(pVerts[topLeftIndex].x, pVerts[topLeftIndex].y, pVerts[topLeftIndex].z);
			Vect topRight = Vect(pVerts[topRightIndex].x, pVerts[topRightIndex].y, pVerts[topRightIndex].z);

			// get AABB data for cell 
			Vect Min = SMathTools::MinVect(bottomLeft, bottomRight);
			Min = SMathTools::MinVect(Min, topLeft);
			Min = SMathTools::MinVect(Min, topRight);

			Vect Max = SMathTools::MaxVect(bottomLeft, bottomRight);
			Max = SMathTools::MaxVect(Max, topLeft);
			Max = SMathTools::MaxVect(Max, topRight);

			cellData newData;
			newData.cellX = x;
			newData.cellZ = z;
			newData.Min = Min;
			newData.Max = Max;

			colInfoList.push_back(newData);

		}

	}

	terrainModel = new Model(pVerts, NUM_VERTS, tlist, NUM_TRIS);

	// delete arrays
	delete [] pVerts;
	delete [] tlist;

	// set up graphics objects
	Vect col = Colors::Green;
	pGoTerrain = new GraphicsObject_TextureFlat(terrainModel, ShaderManager::Get("texture"), texture);
	pTestGo = new GraphicsObject_WireframeConstantColor(terrainModel, ShaderManager::Get("constantColor"), col);

	Matrix world = Matrix(IDENTITY);
	pGoTerrain->SetWorld(world);
	pTestGo->SetWorld(world);

	// we own our iterator
	iterator = new HeightmapTerrainIterator();

}

HeightmapTerrain::~HeightmapTerrain()
{
	delete pGoTerrain;
	delete pTestGo;
	delete terrainModel;
	delete iterator;
}

void HeightmapTerrain::Draw()
{
	pGoTerrain->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}

//draws the wireframe graphics object for the terrain 
void HeightmapTerrain::TestDraw()
{
	pTestGo->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}

Model* HeightmapTerrain::GetTerrainModel()
{
	return this->terrainModel;
}

const std::list<HeightmapTerrain::cellData>& HeightmapTerrain::GetTerrainCollisionInfo() const
{
	return this->colInfoList;
}

HeightmapTerrainIterator* HeightmapTerrain::GetIterator()
{
	iterator->SetTerrain(this);
	return this->iterator;
}

const HeightmapTerrain::cellData& HeightmapTerrain::GetTerrainCell(const Vect& position)
{

	float xDist = -position.X() + (terrainSideLength / 2);
	float zDist = -position.Z() + (terrainSideLength / 2);

	// clamping x and z dist to confines of terrain 

	xDist = SMathTools::Clamp(xDist, 1.0f, terrainSideLength - cellSize); // this is set to 1.0f because zero would allow -1 index
	zDist = SMathTools::Clamp(zDist, 1.0f, terrainSideLength - cellSize);

	// get the correct cell index based on the distance values 

	int xIndex = static_cast<int>(floorf(xDist / cellSize));
	int zIndex = static_cast<int>(floorf(zDist / cellSize));

	// find that cell in cell list 
	int listLoc = xIndex + (zIndex * cellsPerSide);

	CollisionInfoList::iterator it = colInfoList.begin();
	std::advance(it, listLoc);

	return *it;

}

const HeightmapTerrain::cellData& HeightmapTerrain::GetTerrainCell(int x, int z)
{
	int listLoc = x + (z * cellsPerSide);

	CollisionInfoList::iterator it = colInfoList.begin();
	std::advance(it, listLoc);

	return *it;
}

void HeightmapTerrain::GetBSphereCells(const CollisionVolumeBSphere& bs, int& xMin, int& zMin, int& xMax, int& zMax)
{
	// get min and max from bsphere
	Vect minPos = Vect(bs.GetCenter().X() + bs.GetRadius(), 1.0f, bs.GetCenter().Z() + bs.GetRadius());
	Vect maxPos = Vect(bs.GetCenter().X() - bs.GetRadius(), 1.0f, bs.GetCenter().Z() - bs.GetRadius());

	// get cells 
	cellData minCell = this->GetTerrainCell(minPos);
	cellData maxCell = this->GetTerrainCell(maxPos);

	// return cell index values (passing by reference)
	xMin = minCell.cellX;
	zMin = minCell.cellZ;
	xMax = maxCell.cellX;
	zMax = maxCell.cellZ;

	//DataLogger::Add("Min X :  %i  Z :  %i  Max X :  %i  Z :  %i", xMin, zMin, xMax, zMax);

	//// some wacky test code

	//for (int z = zMin; z <= zMax; z++)
	//{

	//	for (int x = xMin; x <= xMax; x++)
	//	{
	//		int listLoc = x + (z * cellsPerSide);
	//		CollisionInfoList::iterator it = colInfoList.begin();
	//		std::advance(it, listLoc);

	//		Visualizer::ShowAABB(it->Min, it->Max, Colors::Yellow);

	//	}

	//}

	return;
}

int HeightmapTerrain::GetCellsPerSide()
{
	return this->cellsPerSide;
}

Vect HeightmapTerrain::getPointNorm(int pointX, int pointZ)
{

	// if we are not on an edge
	// get the six points of the connected tris to where we are
	// calculate incident face normals 
	// average them into the point normal

	Vect pointNormal;

	if (pointX == 0 || pointX == imgWidth - 1 || pointZ == 0 || pointZ == imgWidth - 1) // all edge points 
	{
		pointNormal.set(0.0f, 1.0f, 0.0f, 0.0f); // edge points get arbitrarily set to straight up bc terrain edge shouldnt matter
	}
	else
	{
		// this is point we need to get the normal for 
		Vect point = terrainModel->getVectList()[pointX + (pointZ * imgWidth)];
		// these are the six other connected points 
		Vect pointAbove = terrainModel->getVectList()[pointX + ((pointZ+ 1) * imgWidth)];
		Vect pointBelow = terrainModel->getVectList()[pointX + ((pointZ - 1) * imgWidth)];
		Vect leftPoint = terrainModel->getVectList()[pointX + 1 + (pointZ * imgWidth)];
		Vect rightPoint = terrainModel->getVectList()[pointX - 1 + (pointZ * imgWidth)];
		Vect diagonalUp = terrainModel->getVectList()[pointX - 1 + ((pointZ + 1) * imgWidth)];
		Vect diagonalDown = terrainModel->getVectList()[pointX + 1 + ((pointZ - 1) * imgWidth)];

		// calculate face normals for all connected faces 

		Vect topLeftNorm = (pointAbove - point).cross(leftPoint - point);
		topLeftNorm.norm();

		Vect topMiddleNorm = (diagonalUp - point).cross(pointAbove - point);
		topMiddleNorm.norm();

		Vect topRightNorm = (rightPoint - point).cross(diagonalUp - point);
		topRightNorm.norm();

		Vect bottomNorm = (pointBelow - point).cross(rightPoint - point);
		bottomNorm.norm();

		Vect bottomMiddleNorm = (diagonalDown - point).cross(pointBelow - point);
		bottomMiddleNorm.norm();

		Vect bottomLeftNorm = (leftPoint - point).cross(diagonalDown - point);
		bottomLeftNorm.norm();

		// average all face normals to get point normal 

		float x = (topLeftNorm.X() + topMiddleNorm.X() + topRightNorm.X() + bottomNorm.X() + bottomMiddleNorm.X() + bottomLeftNorm.X()) / 6.0f;
		float y = (topLeftNorm.Y() + topMiddleNorm.Y() + topRightNorm.Y() + bottomNorm.Y() + bottomMiddleNorm.Y() + bottomLeftNorm.Y()) / 6.0f;
		float z = (topLeftNorm.Z() + topMiddleNorm.Z() + topRightNorm.Z() + bottomNorm.Z() + bottomMiddleNorm.Z() + bottomLeftNorm.Z()) / 6.0f;

		pointNormal.set(x, y, z, 0.0f);

	}

	return pointNormal;

}

Vect HeightmapTerrain::GetNormal(const Vect& position)
{

	Vect normal;

	cellData posCell = GetTerrainCell(position);

	Vect bottomRight, bottomLeft, topRight, topLeft;
	
	bottomRight = terrainModel->getVectList()[posCell.cellX + (posCell.cellZ * (cellsPerSide + 1))]; // this is verified to be correct 
	bottomLeft = terrainModel->getVectList()[(posCell.cellX + 1) + (posCell.cellZ * (cellsPerSide + 1))];
	topRight = terrainModel->getVectList()[posCell.cellX + ((posCell.cellZ + 1) * (cellsPerSide + 1))];
	topLeft = terrainModel->getVectList()[(posCell.cellX + 1) + ((posCell.cellZ + 1) * (cellsPerSide + 1))];

	// we need to determine the right tri in this cell 
	
	Vect v2 = position - bottomLeft;
	Vect bottomleftNorm = getPointNorm(posCell.cellX + 1, posCell.cellZ);
	Vect topRightNorm = getPointNorm(posCell.cellX + 1, posCell.cellZ + 1);

	if (-v2.X() > v2.Z()) // top tri 
	{

		float beta = -(position - topRight).X() / cellSize;
		float gamma = (position - topRight).Z() / cellSize;

		// get point normals normals 
		
		Vect topLeftNorm = getPointNorm(posCell.cellX, posCell.cellZ + 1);

		// get interp for normals based on position 
		// QP = QA + Beta (QB - QA) + Gamma (Qc - Qb) 

		normal = topRightNorm + beta * (topLeftNorm - topRightNorm) + gamma * (bottomleftNorm - topLeftNorm);


	}
	else // bottom tri 
	{
		float beta = (position - bottomLeft).X() / cellSize;
		float gamma = -(position - bottomLeft).Z() / cellSize;

		Vect bottomRightNorm = getPointNorm(posCell.cellX, posCell.cellZ);

		normal = bottomleftNorm + beta * (bottomRightNorm - bottomleftNorm) + gamma * (topRightNorm - bottomRightNorm);

	}

	normal.W() = 0.0f;
	return normal;

}

Vect HeightmapTerrain::GetTerrainPoint(const Vect& position)
{
	Vect posVect;
	float yVal;

	cellData posCell = GetTerrainCell(position);

	Vect bottomRight, bottomLeft, topRight, topLeft;

	bottomRight = terrainModel->getVectList()[posCell.cellX + (posCell.cellZ * (cellsPerSide + 1))]; // tri midpoint
	bottomLeft = terrainModel->getVectList()[(posCell.cellX + 1) + (posCell.cellZ * (cellsPerSide + 1))];
	topRight = terrainModel->getVectList()[posCell.cellX + ((posCell.cellZ + 1) * (cellsPerSide + 1))];
	topLeft = terrainModel->getVectList()[(posCell.cellX + 1) + ((posCell.cellZ + 1) * (cellsPerSide + 1))]; // tri midpoint

	Vect v2 = position - bottomLeft;

	if (-v2.X() > v2.Z()) // top tri 
	{

		float beta = -(position - topRight).X() / cellSize;
		float gamma = (position - topRight).Z() / cellSize;

		yVal = topRight.Y() + beta * (topLeft.Y() - topRight.Y()) + gamma * (bottomLeft.Y() - topLeft.Y());

	}
	else // bottom tri 
	{

		float beta = (position - bottomLeft).X() / cellSize;
		float gamma = -(position - bottomLeft).Z() / cellSize;

		yVal = bottomLeft.Y() + beta * (bottomRight.Y() - bottomLeft.Y()) + gamma * (topRight.Y() - bottomRight.Y());
	}

	posVect.set(position.X(), yVal, position.Z(), 1.0f);
	return posVect;
}


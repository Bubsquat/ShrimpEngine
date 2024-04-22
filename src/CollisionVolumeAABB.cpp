// collision volume for axis aligned bounding box

#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "VisualizerAttorney.h"
#include "SMathTools.h"

#include "DataLogger.h"

void CollisionVolumeAABB::ComputeData(Model* mod, const Matrix& mat)
{

	int numPoints = mod->getVectNum();

	// set initial min max values 
	Vect firstPoint = mod->getVectList()[0];
	Min = firstPoint * mat;
	Max = Min;
	

	// run through each point, find actual min max 
	for (int i = 1; i < numPoints; i++)
	{
		// get current point in world space 
		Vect curPoint = mod->getVectList()[i];
		curPoint = curPoint * mat;
		
		// compare to min and max, aggregate min and max point 
		
		if (curPoint.X() < Min.X()) Min.X() = curPoint.X();
		if (curPoint.Y() < Min.Y()) Min.Y() = curPoint.Y();
		if (curPoint.Z() < Min.Z()) Min.Z() = curPoint.Z();

		if (curPoint.X() > Max.X()) Max.X() = curPoint.X();
		if (curPoint.Y() > Max.Y()) Max.Y() = curPoint.Y();
		if (curPoint.Z() > Max.Z()) Max.Z() = curPoint.Z();

	}

	//DataLogger::Add("Min : X: %f Z: %f  Max : X: %f Z: %f", Min.X(), Min.Z(), Max.X(), Max.Z());

	center = (0.5f * (Max + Min));
	locHalfDiagonal = 0.5f * (Max - Min);

}

void CollisionVolumeAABB::ComputeData(const CollisionVolumeBSphere& bs)
{
	float bsRadius = bs.GetRadius();
	Min = bs.GetCenter();
	Min.X() -= bsRadius;
	Min.Y() -= bsRadius;
	Min.Z() -= bsRadius;
	Max = bs.GetCenter();
	Max.X() += bsRadius;
	Max.Y() += bsRadius;
	Max.Z() += bsRadius;

	center = (0.5f * (Max + Min));
	locHalfDiagonal = 0.5f * (Max - Min);
}

void CollisionVolumeAABB::DebugView(const Vect& col) const
{
	VisualizerAttorney::CollisionVolumeAccess::SubmitAABB(*this, col);
}

const Vect& CollisionVolumeAABB::GetMin() const
{
	return Min;
}

const Vect& CollisionVolumeAABB::GetMax() const
{
	return Max;
}

void CollisionVolumeAABB::SetMin(Vect _min)
{
	Min = _min;
	center = (0.5f * (Max + Min));
	locHalfDiagonal = 0.5f * (Max - Min);
}

void CollisionVolumeAABB::SetMax(Vect _max)
{
	Max = _max;
	center = (0.5f * (Max + Min));
	locHalfDiagonal = 0.5f * (Max - Min);
}

bool CollisionVolumeAABB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return SMathTools::IntersectAABB(other, *this);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return SMathTools::IntersectBSphereAABB(other, *this);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return SMathTools::IntersectAABBOBB(other, *this);
}

const Vect& CollisionVolumeAABB::GetLocalHalfDiagonal() const
{
	return locHalfDiagonal;
}

const Matrix& CollisionVolumeAABB::GetWorld() const
{
	return world;
}

const Vect& CollisionVolumeAABB::GetCenter() const
{
	return center;
}
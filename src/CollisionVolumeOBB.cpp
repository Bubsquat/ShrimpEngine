// oriented bounding box for collisision testing 

#include "CollisionVolumeOBB.h"
#include "VisualizerAttorney.h"
#include "SMathTools.h"

void CollisionVolumeOBB::ComputeData(Model* mod, const Matrix& mat)
{

	// update all values
	world = mat;
	locMin = mod->getMinAABB();
	locMax = mod->getMaxAABB();
	locHalfDiagonal = 0.5f * (locMax - locMin); // technically only needs to be computed once but putting it in compute incase model changes 
	center = (locMin + locHalfDiagonal) * world;

}

void CollisionVolumeOBB::DebugView(const Vect& col) const
{
	VisualizerAttorney::CollisionVolumeAccess::SubmitOBB(*this, col);
}

const Vect& CollisionVolumeOBB::GetCenter() const
{
	return center;
}

const Vect& CollisionVolumeOBB::GetLocalHalfDiagonal() const
{	
	return locHalfDiagonal;
}

const Vect& CollisionVolumeOBB::GetLocMin() const
{
	return locMin;
}

const Vect& CollisionVolumeOBB::GetLocMax() const
{
	return locMax;
}

const Matrix& CollisionVolumeOBB::GetWorld() const
{
	return world;
}

//const Vect& CollisionVolumeOBB::GetScale() const
//{
//	return world.get(MatrixRowType::ROW_0).mag
//}

bool CollisionVolumeOBB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return SMathTools::IntersectBSphereOBB(other, *this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeAABB& other) const 
{
	return SMathTools::IntersectAABBOBB(*this, other);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeOBB& other) const 
{
	return SMathTools::IntersectOBB(other, *this);
}
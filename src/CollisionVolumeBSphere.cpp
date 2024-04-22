// Bsphere for collision 

#include "CollisionVolumeBSphere.h"
#include "SMathTools.h"
#include "VisualizerAttorney.h"
#include "CollisionVolumeAABB.h"

CollisionVolumeBSphere::CollisionVolumeBSphere()
{
	Radius = 1.0f;
}

void CollisionVolumeBSphere::ComputeData(Model* mod, const Matrix& mat)
{

	// also not sure what needs to be in our math library so ima skip that for now 

	Vect newCenter;
	float newRadius;
	float newScale;

	newCenter = mod->getCenter();
	newRadius = mod->getRadius();

	newScale = sqrtf(mat.get(MatrixRowType::ROW_0).X() * mat.get(MatrixRowType::ROW_0).X() + mat.get(MatrixRowType::ROW_0).Y() * mat.get(MatrixRowType::ROW_0).Y() + mat.get(MatrixRowType::ROW_0).Z() * mat.get(MatrixRowType::ROW_0).Z());
	
	this->Radius = newRadius * newScale;

	newCenter = newCenter * mat; // this is probably backwards 

	this->Center = newCenter;
}

const Vect& CollisionVolumeBSphere::GetCenter() const 
{
	return this->Center;
}

float CollisionVolumeBSphere::GetRadius() const 
{
	return this->Radius;
}


bool CollisionVolumeBSphere::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return SMathTools::IntersectBSphere(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return SMathTools::IntersectBSphereAABB(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return SMathTools::IntersectBSphereOBB(*this, other);
}


void CollisionVolumeBSphere::DebugView(const Vect& col) const
{
	VisualizerAttorney::CollisionVolumeAccess::SubmitBSphere(*this, col);
}
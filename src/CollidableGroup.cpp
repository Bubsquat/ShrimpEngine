// group of collidable objects of a type 

#include "CollidableGroup.h"
#include "CollidableAttorney.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"


#include "Visualizer.h"
#include "Colors.h"

CollidableGroup::CollidableGroup()
{
	collidableGroupAABB = new CollisionVolumeAABB();
}

CollidableGroup::~CollidableGroup()
{
	delete collidableGroupAABB;
}

const CollidableGroup::CollidableCollection& CollidableGroup::GetColliderCollection()
{
	return this->collidableCollection;
}

void CollidableGroup::Register(Collidable* obj)
{
	CollidableAttorney::Registration::SetDeleteRef(obj, collidableCollection.insert(collidableCollection.end(), obj));
}

void CollidableGroup::Deregister(CollidableCollectionRef ref)
{
	this->collidableCollection.erase(ref);
}

const CollisionVolumeAABB& CollidableGroup::GetGroupAABB()
{
	return *collidableGroupAABB;
}

void CollidableGroup::UpdateGroupCollision()
{

	Vect GroupMin;
	Vect GroupMax;

	// initialize to values we know we will replace 
	collidableGroupAABB->ComputeData(collidableCollection.front()->GetDefaultBSphere());
	GroupMin = collidableGroupAABB->GetMin();
	GroupMax = collidableGroupAABB->GetMax();

	// get total min and max to apply to group AABB
	for (CollidableCollection::iterator it = collidableCollection.begin(); it != collidableCollection.end(); it++)
	{
		float newRad = (*it)->GetDefaultBSphere().GetRadius();
		Vect newMin = (*it)->GetDefaultBSphere().GetCenter();
		newMin.X() -= newRad;
		newMin.Y() -= newRad;
		newMin.Z() -= newRad;

		if (GroupMin.X() > newMin.X()) GroupMin.X() = newMin.X();
		if (GroupMin.Y() > newMin.Y()) GroupMin.Y() = newMin.Y();
		if (GroupMin.Z() > newMin.Z()) GroupMin.Z() = newMin.Z();

		Vect newMax = (*it)->GetDefaultBSphere().GetCenter();
		newMax.X() += newRad;
		newMax.Y() += newRad;
		newMax.Z() += newRad;

		if (GroupMax.X() < newMax.X()) GroupMax.X() = newMax.X();
		if (GroupMax.Y() < newMax.Y()) GroupMax.Y() = newMax.Y();
		if (GroupMax.Z() < newMax.Z()) GroupMax.Z() = newMax.Z();
	}

	collidableGroupAABB->SetMin(GroupMin);
	collidableGroupAABB->SetMax(GroupMax);

	//Visualizer::ShowCollisionVolume(*collidableGroupAABB, Colors::LightPink); // testing code

}
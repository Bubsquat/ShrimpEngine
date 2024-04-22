// command for collision between two different game objects

#include "CollisionTestPairCommand.h"
#include "CollidableGroup.h"
#include "Collidable.h"
#include "CollisionDispatchBase.h"
#include "SMathTools.h"
#include "CollisionVolumeOBB.h"
//
//#include "Visualizer.h"
//#include "CollisionVolumeAABB.h"

CollisionTestPairCommand::CollisionTestPairCommand(CollidableGroup* _g1, CollidableGroup* _g2, CollisionDispatchBase* pd)
	: G1(_g1), G2(_g2), pDispatch(pd)
{}

CollisionTestPairCommand::~CollisionTestPairCommand()
{
	delete pDispatch;
}

void CollisionTestPairCommand::execute()
{
	const CollidableGroup::CollidableCollection& Collection1 = G1->GetColliderCollection();
	const CollidableGroup::CollidableCollection& Collection2 = G2->GetColliderCollection();

	// test the group AABBs before individual tests 

	if (!SMathTools::IntersectAABB(G1->GetGroupAABB(), G2->GetGroupAABB())) return;

	//Visualizer::ShowAABB(G1->GetGroupAABB().GetMin(), G1->GetGroupAABB().GetMax(), Colors::HotPink);
	//Visualizer::ShowAABB(G2->GetGroupAABB().GetMin(), G2->GetGroupAABB().GetMax(), Colors::Crimson);

	// move down to the individual tests

	for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
	{

		for (auto it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
		{

			bool test_result;

			test_result = SMathTools::IntersectBSphereAABB((*it1)->GetDefaultBSphere(), G2->GetGroupAABB()); // test that the BSphere of the first object is colliding with the AABB of the second obj group

			if (test_result) test_result = SMathTools::IntersectBSphere((*it1)->GetDefaultBSphere(), (*it2)->GetDefaultBSphere()); // test BSpheres of both objects

			if (test_result) test_result = SMathTools::Intersect((*it1)->GetCollisionVolume(), (*it2)->GetCollisionVolume()); // only do precise test if bsphere collisionPasses

			if (test_result)
			{
				pDispatch->ProcessCallbacks(*it1, *it2);
			}
		}

	}
}


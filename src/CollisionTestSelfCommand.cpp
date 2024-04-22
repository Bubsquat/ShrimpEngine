// command for a game object colliding with itself 

#include "CollisionTestSelfCommand.h"
#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "Collidable.h"
#include "SMathTools.h"
#include "CollisionVolumeBSphere.h"

CollisionTestSelfCommand::CollisionTestSelfCommand(CollidableGroup* _G, CollisionDispatchBase* _pD)
	: G(_G), pDispatch(_pD)
{}

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
	delete pDispatch;
}

void CollisionTestSelfCommand::execute()
{
	const CollidableGroup::CollidableCollection& Collection1 = G->GetColliderCollection();

	auto it1 = Collection1.begin();

	while(it1 != Collection1.end() && Collection1.size() > 1)
	{
		
		auto it2 = std::next(it1);

		while (it2 != Collection1.end())
		{

			bool test_result;

			test_result = SMathTools::IntersectBSphere((*it1)->GetDefaultBSphere(), (*it2)->GetDefaultBSphere());
				
			if (test_result) test_result = SMathTools::Intersect((*it1)->GetCollisionVolume(), (*it2)->GetCollisionVolume());

			if (test_result)
			{
				pDispatch->ProcessCallbacks(*it1, *it2);
			}

			it2++;

		}
		
		it1++;

	}

}
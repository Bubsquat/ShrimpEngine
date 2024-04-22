// test command for a game object colliding with the level terrain 

#include "CollisionTestTerrainCommand.h"
#include "CollidableGroup.h"
#include "SceneManager.h"
#include "Scene.h"
#include "HeightmapTerrain.h"
#include "HeightmapTerrainIterator.h"
#include "SMathTools.h"
#include "Collidable.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionDispatchBase.h"

#include "Visualizer.h"

CollisionTestTerrainCommand::CollisionTestTerrainCommand(CollidableGroup* _g, CollisionDispatchBase* _pDispatch)
	: g(_g), pDispatch(_pDispatch)
{
	 testAABB = new CollisionVolumeAABB();
}

CollisionTestTerrainCommand::~CollisionTestTerrainCommand()
{
	delete pDispatch;
	delete testAABB;
}

void CollisionTestTerrainCommand::execute()
{

	auto it = g->GetColliderCollection().begin();
	//HeightmapTerrain* terrain = SceneManager::GetCurrentScene()->GetTerrain();	

	// make my iterator 
	cellIterator = SceneManager::GetCurrentScene()->GetTerrain()->GetIterator();

	while (it != g->GetColliderCollection().end() && g->GetColliderCollection().size() >= 1)
	{

		// for each collidable in group test its bsphere against the terrain 
		cellIterator->SetBSphere((*it)->GetDefaultBSphere());

		do 
		{

			testAABB->SetMin(cellIterator->GetCell().Min);
			testAABB->SetMax(cellIterator->GetCell().Max);
			
			if (SMathTools::IntersectBSphereAABB((*it)->GetDefaultBSphere(), *testAABB))
			{
				Visualizer::ShowCollisionVolume(*testAABB, Colors::Red);
				pDispatch->ProcessCallback(*it);
				break;
			}

			//cellIterator++; // this is breaking the iterator 
			cellIterator->operator++();


		} while (cellIterator->GetCell().cellZ != cellIterator->GetEnd().cellZ);

		it++;

	}

}
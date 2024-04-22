// Collision Manager

#include "CollisionManager.h"
#include "CollidableGroup.h"
#include <assert.h>


CollisionManager::STypeID CollisionManager::TypeIDNextNumber = 0;

CollisionManager::CollisionManager()
{
	colGroupCollection.emplace(colGroupCollection.begin(), nullptr);
	colGroupCollection.resize(500, nullptr); // is this correct?
}

CollisionManager::~CollisionManager()
{

	for (CollisionTestCommands::iterator it = collisionTestCommands.begin(); it != collisionTestCommands.end(); it++)
	{
		delete* it;
	}
	collisionTestCommands.clear();


	for (CollidableGroupCollection::iterator it = colGroupCollection.begin(); it != colGroupCollection.end(); it++)
	{
		delete (*it);
	}

}

void CollisionManager::ProcessCollisions()
{

	for (CollidableGroupCollection::iterator it = colGroupCollection.begin(); it != colGroupCollection.end(); it++) // update colgroup aabb once per frame  
	{
		if ((*it) != nullptr) // cause of how the colGroupCollection is there are like 500 initialized empty so this runs more than it should atm 
		{
			if (!(*it)->GetColliderCollection().empty()) (*it)->UpdateGroupCollision();
		}		
	}

	for (CollisionTestCommands::iterator it = collisionTestCommands.begin(); it != collisionTestCommands.end(); it++)
	{
		(*it)->execute();
	}

}

void CollisionManager::SetGroupForTypeID(CollisionManager::STypeID ind)
{
	if (colGroupCollection[ind] == nullptr) colGroupCollection[ind] = new CollidableGroup();
}

CollidableGroup* CollisionManager::GetColGroup(STypeID id)
{
	assert(colGroupCollection[id]); // make sure the group exists 
	return colGroupCollection[id];
}
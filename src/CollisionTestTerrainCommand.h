// test command for a game object colliding with the level terrain 

#ifndef _CollisionTestTerrainCommand
#define _CollisionTestTerrainCommand

#include "CollisionTestCommandBase.h"

class CollidableGroup;
class CollisionDispatchBase;
class CollisionVolumeAABB;
class HeightmapTerrainIterator;

class CollisionTestTerrainCommand : public CollisionTestCommandBase
{
public:

	CollisionTestTerrainCommand() = delete;
	CollisionTestTerrainCommand(CollidableGroup* g, CollisionDispatchBase* _pDispatch);
	CollisionTestTerrainCommand(const CollisionTestTerrainCommand&) = delete;
	CollisionTestTerrainCommand& operator=(const CollisionTestTerrainCommand&) = delete;
	~CollisionTestTerrainCommand();

	void execute();

private:

	CollidableGroup* g;
	CollisionVolumeAABB* testAABB;
	CollisionDispatchBase* pDispatch;
	HeightmapTerrainIterator* cellIterator;
};


#endif _CollisionTestTerrainCommand

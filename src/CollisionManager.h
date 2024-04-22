// Collision Manager

#ifndef _CollisionManager
#define _CollisionManager

#include "AzulCore.h"
#include <vector>
#include <list>
#include "CollisionDispatchBase.h"
#include "CollisionDispatch.h"
#include "CollisionDispatchSingle.h"
#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"
#include "CollisionTestTerrainCommand.h"

class CollidableGroup;
class CollisionTestCommandBase;

class CollisionManager
{
public:
	using STypeID = int;
	static const STypeID SID_UNDEFINED = -1;

	CollisionManager();
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
	~CollisionManager();

	CollidableGroup* GetColGroup(STypeID id);
	void ProcessCollisions();

private:
	static STypeID TypeIDNextNumber; // = 0;

	using CollidableGroupCollection = std::vector<CollidableGroup*>;
	CollidableGroupCollection colGroupCollection;

	using CollisionTestCommands = std::list<CollisionTestCommandBase*>;
	CollisionTestCommands collisionTestCommands;

	void SetGroupForTypeID(CollisionManager::STypeID ind);

public:
	template <typename C>
	STypeID GetTypeID()
	{
		static STypeID myTypeID = TypeIDNextNumber++;
		SetGroupForTypeID(myTypeID); 

		return myTypeID;
	}

	template<typename C1, typename C2>
	void SetCollisionPair()
	{
		CollidableGroup* g1 = colGroupCollection[GetTypeID<C1>()];
		CollidableGroup* g2 = colGroupCollection[GetTypeID<C2>()];
		CollisionDispatch<C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();

		collisionTestCommands.push_back(new CollisionTestPairCommand(g1, g2, pDispatch));
	}
	
	template<typename C1>
	void SetCollisionSelf()
	{
		CollidableGroup* g = colGroupCollection[GetTypeID<C1>()];
		CollisionDispatch<C1, C1>* pDispatch = new CollisionDispatch<C1, C1>(); // double check this line

		collisionTestCommands.push_back(new CollisionTestSelfCommand(g, pDispatch));
	}

	template<typename C1>
	void SetCollisionTerrain()
	{
		CollidableGroup* g = colGroupCollection[GetTypeID<C1>()];
		CollisionDispatchSingle<C1>* pDispatch = new CollisionDispatchSingle<C1>();
		collisionTestCommands.push_back(new CollisionTestTerrainCommand(g, pDispatch));
	}
};

#endif _CollisionManager

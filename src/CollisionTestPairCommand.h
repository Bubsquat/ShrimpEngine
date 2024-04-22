// command for collision between two different game objects

#ifndef _CollisionTestPairCommand
#define _CollisionTestPairCommand

#include "CollisionTestCommandBase.h"

class CollisionDispatchBase;
class CollidableGroup;

class CollisionTestPairCommand : public CollisionTestCommandBase
{
public:
	//CollisionTestPairCommand(); // these were in the signiture 
	CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd);
	//CollisionTestPairCommand(const CollisionTestPairCommand&);
	~CollisionTestPairCommand();

	void execute();

private:

	CollisionDispatchBase* pDispatch;
	CollidableGroup* G1;
	CollidableGroup* G2;
};



#endif _CollisionTestPairCommand


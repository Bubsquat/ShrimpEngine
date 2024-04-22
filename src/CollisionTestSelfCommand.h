// command for a game object colliding with itself 

#ifndef _CollisionTestSelfCommand
#define _CollisionTestSelfCommand

#include "CollisionTestCommandBase.h"

class CollidableGroup;
class CollisionDispatchBase;

class CollisionTestSelfCommand : public CollisionTestCommandBase
{
public:

	CollisionTestSelfCommand(CollidableGroup*, CollisionDispatchBase* pd);
	~CollisionTestSelfCommand();

	void execute();

private:
	CollisionDispatchBase* pDispatch;
	CollidableGroup* G;
};



#endif _CollisionTestSelfCommand

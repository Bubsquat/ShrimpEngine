// base class for the types of collision tests 

#ifndef _CollisionTestCommandBase
#define _CollisionTestCommandBase

class CollisionTestCommandBase
{
public:

	CollisionTestCommandBase() = default;
	CollisionTestCommandBase(const CollisionTestCommandBase&) = delete;
	CollisionTestCommandBase& operator= (const CollisionTestCommandBase&) = delete;
	virtual ~CollisionTestCommandBase() {};

	virtual void execute() = 0;
};



#endif _CollisionTestCommandBase

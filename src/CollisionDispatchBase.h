// non templetized base class for collision dispatches 

#ifndef _CollisionDispatchBase
#define _CollisionDispatchBase

class Collidable;

class CollisionDispatchBase
{
public:

	CollisionDispatchBase() = default;
	CollisionDispatchBase(const CollisionDispatchBase&) = delete;
	CollisionDispatchBase& operator= (const CollisionDispatchBase&) = delete;
	virtual ~CollisionDispatchBase() {};

	virtual void ProcessCallbacks(Collidable* c1, Collidable* c2) = 0;
	virtual void ProcessCallback(Collidable* c1) = 0;
};



#endif _CollisionDispatchBase


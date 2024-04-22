// templetized class for single collision dispatch

#ifndef _CollisionDispatchSingle
#define _CollisionDispatchSingle

#include "CollisionDispatchBase.h"
#include <assert.h>

class Collidable;

template <typename C1>

class CollisionDispatchSingle : public CollisionDispatchBase
{
public:

	CollisionDispatchSingle() = default;
	CollisionDispatchSingle(const CollisionDispatchSingle&) = delete;
	CollisionDispatchSingle& operator = (const CollisionDispatchSingle&) = delete;
	~CollisionDispatchSingle() {};

	virtual void ProcessCallback(Collidable* c1)
	{
		C1* pDerCol1 = static_cast<C1*>(c1);
		pDerCol1->CollisionTerrain();
	}

	virtual void ProcessCallbacks(Collidable*, Collidable*)
	{
		assert("Wrong callback used");
	}
};


#endif _CollisionDispatchSingle


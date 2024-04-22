// templetized class for collision dispatch 

#ifndef _CollisionDispatch
#define _CollisionDispatch

#include "CollisionDispatchBase.h"
#include <assert.h>

class Collidable;

template <typename C1, typename C2>

class CollisionDispatch : public CollisionDispatchBase
{
public:

	CollisionDispatch() = default;
	CollisionDispatch(const CollisionDispatch&) = delete;
	CollisionDispatch& operator = (const CollisionDispatch&) = delete;
	~CollisionDispatch() {};

	virtual void ProcessCallbacks(Collidable* c1, Collidable* c2)
	{
		C1* pDerCol1 = static_cast<C1*>(c1);
		C2* pDerCol2 = static_cast<C2*>(c2);

		pDerCol1->Collision(pDerCol2);
		pDerCol2->Collision(pDerCol1);
	}

	virtual void ProcessCallback(Collidable*)
	{
		assert("Wrong callback used");
	}

};


#endif _CollisionDispatch


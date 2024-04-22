// attorney class for the collidable attribute 

#ifndef _CollidableAttorney
#define _CollidableAttorney

#include "Collidable.h"

class CollidableAttorney
{
public:

	class Registration
	{
		friend class CollidableRegistrationCommand;
		friend class CollidableDeregistrationCommand;
		friend class CollidableGroup; // check for include loops here 
		friend class Scene;
	private:
		static void SetDeleteRef(Collidable* obj, CollidableGroup::CollidableCollectionRef ref) { obj->SetDeleteRef(ref); };
		static CollidableGroup::CollidableCollectionRef GetDeleteRef(Collidable* obj) { return obj->GetDeleteRef(); };
		static void SceneRegistration(Collidable* obj) { obj->SceneRegistration(); };
		static void SceneDeregistration(Collidable* obj) { obj->SceneDeregistration(); };
		static CollisionManager::STypeID GetCollidableId(Collidable* obj) { return obj->GetTypeId(); };
	};

};


#endif _CollidableAttorney


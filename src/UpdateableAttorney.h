// Attorney for updatable attribute

#ifndef _UpdateableAttorney
#define _UpdateableAttorney

#include "Updateable.h"

class UpdateableAttorney
{
public:
	class GameLoop
	{
	private:
		friend class UpdateableManager;
		static void Update(Updateable* obj) { obj->Update(); };
		static void SetListRef(Updateable* obj, UpdateableManager::UpdateListRef ref) { obj->SetListRef(ref); };
		static UpdateableManager::UpdateListRef GetListRef(Updateable* obj) { return obj->GetListRef(); };
	};
public:
	class Registration
	{
		friend class UpdateRegistrationCommand;
		friend class UpdateDeregistrationCommand;
	private:
		static void SceneRegistration(Updateable* obj) { obj->SceneRegistration(); };
		static void SceneDeregistration(Updateable* obj) { obj->SceneDeregistration(); };
	};

};



#endif _UpdateableAttorney


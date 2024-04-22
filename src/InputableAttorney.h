// attorney for inputable attribute

#ifndef _InputableAttorney
#define _InputableAttorney

#include "Inputable.h"

class InputableAttorney
{
public:
	class GameLoop
	{
		friend class SingleKeyEventManager;
	private:
		static void SetDeleteRef(Inputable* obj, SingleKeyEventManager::InputListRef ref) { obj->SetDeleteRef(ref); };
		SingleKeyEventManager::InputListRef GetDeleteRef(Inputable* obj) { return obj->GetDeleteRef(); };
	};

public:
	class Registration
	{
		friend class InputRegistrationCommand;
		friend class InputDeregistrationCommand;
	private:
		static void SceneRegistration(Inputable* obj, AZUL_KEY k, KeyboardEvents ev) { obj->SceneRegistration(k, ev); };
		static void SceneDeregistration(Inputable* obj, AZUL_KEY k, KeyboardEvents ev) { obj->SceneDeregistration(k, ev); };
	};


};




#endif _InputableAttorney


// attorney class for acessing scene functions 

#ifndef _SceneAttorney
#define _SceneAttorney

//#include "SceneManager.h"
#include "Scene.h"

class CollisionManager;

class SceneAttorney
{
public:

	class Registration
	{
		friend class Updateable;
		friend class Drawable;
		friend class Alarmable;
		friend class Inputable;
		friend class GameObject;
		friend class Collidable;
	private:
		static void Register(Scene* scene, Updateable* obj) { scene->Register(obj); };
		static void Register(Scene* scene, Drawable* obj) { scene->Register(obj); };
		static void Register(Scene* scene, Alarmable* obj, AlarmableManager::ALARM_ID id, float t) { scene->Register(obj, id, t); };
		static void Register(Scene* scene, Inputable* obj, AZUL_KEY k, KeyboardEvents ev) { scene->Register(obj, k, ev); };
		static void Register(Scene* scene, Collidable* obj) { scene->Register(obj); };

		static void Deregister(Scene* scene, Updateable* obj) { scene->Deregister(obj); };
		static void Deregister(Scene* scene, Drawable* obj) { scene->Deregister(obj); };
		static void Deregister(Scene* scene, Alarmable* obj, AlarmableManager::ALARM_ID id) { scene->Deregister(obj, id); };
		static void Deregister(Scene* scene, Inputable* obj, AZUL_KEY k, KeyboardEvents ev) { scene->Deregister(obj, k, ev); };
		static void Deregister(Scene* scene, Collidable* obj) { scene->Deregister(obj); };

		static void SubmitCommand(Scene* scene, RegistrationCommand* cmd) { scene->SubmitCommand(cmd); };

		static CollisionManager* GetCollisionMgr(Scene* scene) { return scene->GetCollisionMgr(); };
	};

};


#endif _SceneAttorney

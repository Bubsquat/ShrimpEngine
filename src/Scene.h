// scene for handeling game objects 

#ifndef _Scene
#define _Scene

class Updateable;
class UpdateableManager;
class Drawable;
class DrawableManager;
class RegistrationCommand;
class SceneRegistrationBroker;
class Alarmable;
class Inputable;
class KeyboardEventManager;
class CameraManager;
class CollisionManager;
class Collidable;
class HeightmapTerrain;

#include "AlarmableManager.h"
#include "AzulCore.h"
#include "KeyboardEvents.h"

class Scene
{

	friend class SceneAttorney;

public:

	Scene(); 
	Scene(const Scene&) = delete;
	Scene& operator =(const Scene&) = delete;
	virtual ~Scene();

	void Draw();
	void Draw2D();
	virtual void Initialize();
	virtual void SceneEnd();
	void Update();
	CameraManager* GetCameraManager();
	void SetTerrain(const std::string terrainName);
	HeightmapTerrain* GetTerrain();

private:

	UpdateableManager* updateManager;
	DrawableManager* drawManager; 
	AlarmableManager* alarmManager;
	KeyboardEventManager* keyboardManager;
	CameraManager* cameraManager;
	CollisionManager* collisionManager;
	SceneRegistrationBroker* regBrkr;
	HeightmapTerrain* pTerrain;

	void Register(Updateable*);
	void Deregister(Updateable*);
	void Register(Drawable*);
	void Deregister(Drawable*);
	void Register(Alarmable* obj, AlarmableManager::ALARM_ID id, float t);
	void Deregister(Alarmable* obj, AlarmableManager::ALARM_ID id);
	void Register(Inputable* obj, AZUL_KEY k, KeyboardEvents ev);
	void Deregister(Inputable* obj, AZUL_KEY k, KeyboardEvents ev);
	void Register(Collidable* obj);
	void Deregister(Collidable* obj);
	void SubmitCommand(RegistrationCommand* cmd);
	CollisionManager* GetCollisionMgr();
	

protected:

	template<typename C1, typename C2>
	void SetCollisionPair()
	{
		collisionManager->SetCollisionPair<C1, C2>();
	}

	template<typename C1>
	void SetCollisionSelf()
	{
		collisionManager->SetCollisionSelf<C1>();
	}

	template<typename C1>
	void SetCollisionTerrain()
	{
		collisionManager->SetCollisionTerrain<C1>();
	}

};



#endif _Scene

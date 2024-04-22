// scene for handeling game objects 

#include "Scene.h"
#include "UpdateableManager.h"
#include "DrawableManager.h"
//#include "Updateable.h"
//#include "Drawable.h"
//#include "Alarmable.h"
#include "CollidableAttorney.h"
#include "SceneRegistrationBroker.h"
#include "RegistrationCommand.h"
#include "KeyboardEventManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "TerrainManager.h"
#include "HeightmapTerrain.h"

Scene::Scene()
{
	updateManager = new UpdateableManager();
	drawManager = new DrawableManager(); 
	alarmManager = new AlarmableManager();
	keyboardManager = new KeyboardEventManager();
	cameraManager = new CameraManager();
	collisionManager = new CollisionManager();
	regBrkr = new SceneRegistrationBroker();
	pTerrain = nullptr; // replace this with a nullterrain later
}

Scene::~Scene()
{
	delete updateManager; 
	delete drawManager; 
	delete alarmManager;
	delete keyboardManager;
	delete cameraManager;
	delete collisionManager;
	delete regBrkr; 
}

void Scene::Register(Updateable* obj)
{
	this->updateManager->Register(obj);
}

void Scene::Deregister(Updateable* obj)
{
	this->updateManager->Deregister(obj);
}

void Scene::Register(Drawable* obj)
{
	this->drawManager->Register(obj);
}

void Scene::Deregister(Drawable* obj)
{
	this->drawManager->Deregister(obj);
}

void Scene::Register(Alarmable* obj, AlarmableManager::ALARM_ID id, float t)
{
	this->alarmManager->Register(t, obj, id);
}

void Scene::Deregister(Alarmable* obj, AlarmableManager::ALARM_ID id)
{
	this->alarmManager->Deregister(obj, id);
}

void Scene::Register(Inputable* obj, AZUL_KEY k, KeyboardEvents ev)
{
	this->keyboardManager->Register(obj, k, ev);
}

void Scene::Deregister(Inputable* obj, AZUL_KEY k, KeyboardEvents ev)
{
	this->keyboardManager->Deregister(obj, k, ev);
}

void Scene::Register(Collidable* obj)
{
	this->collisionManager->GetColGroup(CollidableAttorney::Registration::GetCollidableId(obj))->Register(obj); // this might be the wrong way of doing it 
}

void Scene::Deregister(Collidable* obj)
{
	this->collisionManager->GetColGroup(CollidableAttorney::Registration::GetCollidableId(obj))->Deregister(CollidableAttorney::Registration::GetDeleteRef(obj));
}

void Scene::Update()
{
	this->regBrkr->executeCommands(); // this has to happen first

	this->collisionManager->ProcessCollisions();

	this->alarmManager->ProcessAlarms();
	this->keyboardManager->ProcessKeyEvents();
	this->updateManager->ProcessElements();

}

void Scene::Draw()
{
	this->GetCameraManager()->UpdateDefaultCam();
	this->GetCameraManager()->UpdateCurrentCamera();
	this->GetCameraManager()->Update2DCamera();
	if (pTerrain) this->pTerrain->Draw();
	//if (pTerrain) this->pTerrain->TestDraw();
	this->drawManager->ProcessElements();
}

void Scene::SubmitCommand(RegistrationCommand* cmd)
{
	regBrkr->addCommands(cmd);
}

CameraManager* Scene::GetCameraManager()
{
	return this->cameraManager;
}

CollisionManager* Scene::GetCollisionMgr()
{
	return this->collisionManager;
}

void Scene::SetTerrain(const std::string terrainName)
{
	this->pTerrain = TerrainManager::Get(terrainName);
}

HeightmapTerrain* Scene::GetTerrain()
{
	return this->pTerrain;
}

// to be defined by users 

void Scene::Initialize()
{}


void Scene::SceneEnd()
{}

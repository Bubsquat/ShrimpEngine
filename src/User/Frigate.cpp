// demo frigate 

#include "Frigate.h"
#include "../SceneManager.h"
#include "../ModelManager.h"
#include "../TextureManager.h"
#include "../ShaderManager.h"
#include "../CameraManager.h"
#include "../Scene.h"
#include "DemoGameScene.h"
#include "../Visualizer.h"

Frigate::Frigate()
{

	// setting up frigate game object 

	// create graphics objs

	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::Get("frigateModel"), ShaderManager::Get("textureLight"), TextureManager::Get("frigateTex"), LightColor, LightPos);

	//Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	//pGObj_SpaceshipBSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("sphereModel"), ShaderManager::Get("constantColor"), Blue);

	Matrix world;

	// Spaceship
	ShipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
	ShipRotTrans = Matrix(ROT_Y, 0) * Matrix(TRANS, 0, 20, 0);
	world = ShipScale * ShipRotTrans;
	pGObj_SpaceFrigateLight->SetWorld(world);

	// collision testing
	SetColliderModel(pGObj_SpaceFrigateLight->getModel(), VOLUME_TYPE::AABB);
	SetCollidableGroup<Frigate>();
	Collidable::UpdateCollisionData(world);


	GameObject::SubmitEntry();
}

void Frigate::SceneEntry()
{
	// collision testing 
	SubmitCollisionRegistration();

	// register everything
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, KeyboardEvents::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, KeyboardEvents::KEY_RELEASE);
	GameObject::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 8.0f);
	
}

void Frigate::SceneExit()
{
	// deregister everything 
	SubmitCollisionDeregistration();
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_A, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_D, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_W, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_S, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, KeyboardEvents::KEY_PRESS);
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_SPACE, KeyboardEvents::KEY_RELEASE);
}

void Frigate::Alarm0()
{
	GameObject::SubmitExit();
	GameObject::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_1, 3.0f);
	
	//DemoGameScene* newScene = new DemoGameScene();
	//SceneManager::SubmitSceneChange(newScene);

}

void Frigate::Alarm1()
{
	GameObject::SubmitEntry();
}

void Frigate::KeyHolding(AZUL_KEY k)
{

	if (k == AZUL_KEY::KEY_A)
	{
		ShipRotTrans = Matrix(ROT_Y, ShipRotAng) * ShipRotTrans;
	}

	if (k == AZUL_KEY::KEY_D)
	{
		ShipRotTrans = Matrix(ROT_Y, -ShipRotAng) * ShipRotTrans;
	}

	if (k == AZUL_KEY::KEY_W)
	{
	ShipRotTrans = Matrix(TRANS, Vect(0, 0, ShipTransSpeed)) * ShipRotTrans;
	}

	if (k == AZUL_KEY::KEY_S)
	{
		ShipRotTrans = Matrix(TRANS, Vect(0, 0, -ShipTransSpeed)) * ShipRotTrans;
	}

}

void Frigate::KeyReleased(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE)
	{
		BsphereToggle = true;
		DebugMsg::out("Bounding sphere: On\n");

	}

}

void Frigate::KeyPressed(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE)
	{
		BsphereToggle = false;
		DebugMsg::out("Bounding sphere: Off\n");
	}


	

}

void Frigate::Update()
{


	// Spaceship adjust matrix

	Matrix world = ShipScale * ShipRotTrans;
	pGObj_SpaceFrigateLight->SetWorld(world);


	//*
	// Adjusting the spaceship's bounding sphere
	Vect vBSSize = pGObj_SpaceFrigateLight->getModel()->getRadius() * Vect(1, 1, 1);
	Vect vBSPos = pGObj_SpaceFrigateLight->getModel()->getCenter();

	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	//Matrix worldBS = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos) * world;

	//pGObj_SpaceshipBSphere->SetWorld(worldBS);

	// collision testing
	Collidable::UpdateCollisionData(world);

	//Visualizer::ShowBSphere(Collidable::GetBSphere());
}

void Frigate::Draw()
{

	// collision testing 
	//Visualizer::ShowBSphere(Collidable::GetBSphere());
	Visualizer::ShowCollisionVolume(Collidable::GetCollisionVolume());

	pGObj_SpaceFrigateLight->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	//if (BsphereToggle)
	//{
	//	pGObj_SpaceshipBSphere->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
	//}

}

Frigate::~Frigate()
{
	delete pGObj_SpaceFrigateLight;
	//delete pGObj_SpaceshipBSphere;
}

void Frigate::Collision(Frigate*)
{
	DebugMsg::out("Frigate: Self Collision\n");
}
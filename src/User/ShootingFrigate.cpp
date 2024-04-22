// frigate that shoots and is controlled by the player 

#include "ShootingFrigate.h"
#include "../ModelManager.h"
#include "../ShaderManager.h"
#include "../TextureManager.h"
#include "../SceneManager.h"
#include "../Scene.h"
#include "../CameraManager.h"
#include "../Visualizer.h"
#include "../Colors.h"
#include "../DataLogger.h"

#include "DemoScene1.h"

#include "../CollisionVolumeBSphere.h"
#include "../HeightmapTerrain.h"

ShootingFrigate::ShootingFrigate()
{
	// setting up frigate game object 
	
	// create graphics objs

	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::Get("frigateModel"), ShaderManager::Get("textureLight"), TextureManager::Get("frigateTex"), LightColor, LightPos);

	Matrix world;

	// Spaceship
	ShipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
	ShipRotTrans = Matrix(ROT_Y, 0) * Matrix(TRANS, 0, 20, 0);
	world = ShipScale * ShipRotTrans;
	pGObj_SpaceFrigateLight->SetWorld(world);

	// collision testing
	collide = false;
	Collidable::SetColliderModel(pGObj_SpaceFrigateLight->getModel(), VOLUME_TYPE::OBB);
	Collidable::UpdateCollisionData(world);
	SetCollidableGroup<ShootingFrigate>();

	GameObject::SubmitEntry();
}

ShootingFrigate::~ShootingFrigate()
{
	delete pGObj_SpaceFrigateLight;
}

void ShootingFrigate::SceneEntry()
{
	// register everything
	SubmitCollisionRegistration();
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_A, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_D, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_W, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_S, KeyboardEvents::KEY_HOLDING);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, KeyboardEvents::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_M, KeyboardEvents::KEY_PRESS);

}

void ShootingFrigate::SceneExit()
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
	Inputable::SubmitKeyDeregistration(AZUL_KEY::KEY_M, KeyboardEvents::KEY_PRESS);
}

void ShootingFrigate::Update()
{
	Matrix world = ShipScale * ShipRotTrans;
	pGObj_SpaceFrigateLight->SetWorld(world);
	Collidable::UpdateCollisionData(world);

	Vect normal = SceneManager::GetCurrentScene()->GetTerrain()->GetNormal(ShipRotTrans.get(ROW_3));
	Vect pos = SceneManager::GetCurrentScene()->GetTerrain()->GetTerrainPoint(ShipRotTrans.get(ROW_3));

	Visualizer::ShowRay(pos, normal, Colors::Red);

}

void ShootingFrigate::Draw()
{

	Matrix testM = Matrix(TRANS, 35, 10, 35) * ShipRotTrans;

	Visualizer::ShowCollisionVolume(Collidable::GetDefaultBSphere(), Colors::Azure);
	Visualizer::ShowLine(ShipRotTrans.get(MatrixRowType::ROW_3), ShipRotTrans.get(MatrixRowType::ROW_1), Colors::White);

	pGObj_SpaceFrigateLight->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	//if (collide)
	//{
	//	//Visualizer::ShowBSphere(Collidable::GetBSphere(), Colors::Red);
	//	Visualizer::ShowCollisionVolume(Collidable::GetCollisionVolume(), Colors::Red);
	//	collide = false;
	//}
	//else
	//{
	//	//Visualizer::ShowBSphere(Collidable::GetBSphere(), Colors::Blue);
	//	Visualizer::ShowCollisionVolume(Collidable::GetCollisionVolume(), Colors::Blue);
	//}
}

void ShootingFrigate::KeyHolding(AZUL_KEY k)
{

	if (k == AZUL_KEY::KEY_A)
	{
		ShipRotTrans = Matrix(ROT_Y, ShipRotAng) * ShipRotTrans;
		//Visualizer::ShowBSphere(Collidable::GetBSphere());
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

void ShootingFrigate::KeyPressed(AZUL_KEY k)
{
	// shoot a bullet here

	if (k == AZUL_KEY::KEY_SPACE)
	{
		myBulletFactory.CreateBullet(ShipRotTrans);
	}

	if (k == AZUL_KEY::KEY_M)
	{
		DemoScene1* newScene = new DemoScene1();
		SceneManager::SubmitSceneChange(newScene);
	}
}

void ShootingFrigate::Collision(Cottage*)
{
	DebugMsg::out("SFrigate: Collided with cottage\n");
	collide = true;
}

void ShootingFrigate::Collision(ShootingFrigate*)
{
	DebugMsg::out("SFrigate: Self Collision\n");
}

Vect ShootingFrigate::getPos()
{
	return ShipRotTrans.get(MatrixRowType::ROW_3);
}

void ShootingFrigate::CollisionTerrain()
{
	DebugMsg::out("Collided with terrian\n");
}
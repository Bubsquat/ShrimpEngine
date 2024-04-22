// static cottage

#include "Cottage.h"
#include "../ModelManager.h"
#include "../ShaderManager.h"
#include "../TextureManager.h"
#include "../SceneManager.h"
#include "../CameraManager.h"
#include "../Visualizer.h"
#include "../Colors.h"

#include "../CollisionVolumeBSphere.h"

Cottage::Cottage()
{

	// create graphics objs
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_CottageLight = new GraphicsObject_TextureLight(ModelManager::Get("cottageModel"), ShaderManager::Get("textureLight"), TextureManager::Get("cottageTex"), TextureManager::Get("roofTex"), TextureManager::Get("brickTex") , TextureManager::Get("chimneyTex"), LightColor, LightPos);

	// place obj
	Matrix world;

	Scale.set(SCALE, 5.0f, 5.0f, 5.0f);
	RotTrans = Matrix(ROT_Y, 0) * Matrix(TRANS, 80, 0, -100);
	world = Scale * RotTrans;
	pGObj_CottageLight->SetWorld(world);

	GameObject::SubmitEntry();
}

Cottage::~Cottage()
{
	delete pGObj_CottageLight;
}

void Cottage::SceneEntry()
{
	//collision testing 
	collide = false;
	Collidable::SetColliderModel(pGObj_CottageLight->getModel(), VOLUME_TYPE::OBB);
	Collidable::UpdateCollisionData(Scale*RotTrans);
	Collidable::SetCollidableGroup<Cottage>();

	Updateable::SubmitUpdateRegistration();
	Collidable::SubmitCollisionRegistration();
	Drawable::SubmitDrawRegistration();
}

void Cottage::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Collidable::SubmitCollisionDeregistration();
	Drawable::SubmitDrawDeregistration();
}

void Cottage::Update()
{
	
	Matrix world = Scale * RotTrans;
	pGObj_CottageLight->SetWorld(world);
	Collidable::UpdateCollisionData(world);
}

void Cottage::Draw()
{
	Visualizer::ShowCollisionVolume(Collidable::GetDefaultBSphere());
	pGObj_CottageLight->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

	if (collide)
	{
		//Visualizer::ShowBSphere(Collidable::GetBSphere(), Colors::Red);
		Visualizer::ShowCollisionVolume(Collidable::GetCollisionVolume(), Colors::Red);
		collide = false;
	}	
	else
	{
		//Visualizer::ShowBSphere(Collidable::GetBSphere(), Colors::Blue);
		Visualizer::ShowCollisionVolume(Collidable::GetCollisionVolume(), Colors::Blue);
	}
		
}

void Cottage::Collision(ShootingFrigate* obj)
{
	obj;
	DebugMsg::out("Cottage: Collided with frigate\n");

	collide = true;

}

void Cottage::Collision(Bullet*)
{
	DebugMsg::out("Cottage: Collided with Bullet\n");
	collide = true;
}

void Cottage::SetPosition(Vect _pos)
{
	this->RotTrans = Matrix(TRANS, _pos);
}
// bullet that travels forwards and has a lifetime 

#include "Bullet.h"
#include "../SceneManager.h"
#include "../ModelManager.h"
#include "../TextureManager.h"
#include "../ShaderManager.h"
#include "../CameraManager.h"
#include "../Scene.h"
#include "../Colors.h"
#include "../HeightmapTerrain.h"
#include "BulletFactory.h"

Bullet::Bullet()
{

	Vect BulletColor = Colors::Red;
	this->pGObj_Bullet = new GraphicsObject_WireframeConstantColor(ModelManager::Get("sphereModel"), ShaderManager::Get("constantColor"), BulletColor);

	speed =55.0;
	lifetime = 6.0f;

	// collision testing 
	Collidable::SetColliderModel(pGObj_Bullet->getModel(), VOLUME_TYPE::BSPHERE);
	SetCollidableGroup<Bullet>();
	
}

Bullet::~Bullet()
{
	delete this->pGObj_Bullet;
}

void Bullet::SceneEntry()
{
	SubmitCollisionRegistration();
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, lifetime);
}

void Bullet::SceneExit()
{
	SubmitCollisionDeregistration();
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
	myFactory->RecycleBullet(this); // factory recycling needs to be in scene exit, now I know 
	
}

void Bullet::Update()
{
	RotTrans = Matrix(TRANS, Vect(0, 0, speed)) * RotTrans; // move forwards 

	Matrix world = Scale * RotTrans;
	pGObj_Bullet->SetWorld(world);
	Collidable::UpdateCollisionData(world);


	// despawn proj that are under terrain without having to do collision checks 

	Vect validPos = SceneManager::GetCurrentScene()->GetTerrain()->GetTerrainPoint(RotTrans.get(ROW_3));
	if (validPos.Y() > RotTrans.get(ROW_3).Y()) SubmitExit();
	
}

void Bullet::Draw()
{
	this->pGObj_Bullet->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}

void Bullet::Alarm0()
{
	// lifetime has ended leave scene  
	this->SubmitExit();
	//myFactory->RecycleBullet(this);
}

void Bullet::Initialize(Matrix _RotTrans)
{

	Matrix world;

	Scale.set(SCALE, 5.5f, 5.5f, 7.0f);
	RotTrans = _RotTrans; 
	world = Scale * RotTrans;
	pGObj_Bullet->SetWorld(world);
	Collidable::UpdateCollisionData(world);

}

void Bullet::SetFactory(BulletFactory* factory)
{
	myFactory = factory;
}

void Bullet::Collision(Bullet*)
{
	DebugMsg::out("Bullet: Collided with self\n");
	this->SubmitExit();
}

void Bullet::Collision(IKTank*)
{

}

//void Bullet::CollisionTerrain()
//{
//	this->SubmitExit();
//}

void Bullet::Collision(Cottage*)
{
	DebugMsg::out("Bullet: Collided with Cottage\n");
}

void Bullet::Collision(Tank*)
{
	DebugMsg::out("Bullet: collided with Tank\n");
	this->SubmitExit();
}
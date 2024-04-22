// tank 

#include "Tank.h"
#include "../ModelManager.h"
#include "../TextureManager.h"
#include "../ShaderManager.h"
#include "../SceneManager.h"
#include "../CameraManager.h"
#include "../Colors.h"
#include "BulletFactory.h"
#include "TankTurret.h"
#include "TankLeg.h"
#include "../Visualizer.h"
#include "TankControllerBaseClass.h"

Tank::Tank(BulletFactory* _pBulletFactory, float Xpos, float Zpos)
{

	pBulletFactory = _pBulletFactory;

	XYZRot = Vect(0.0f, 0.0f, 0.0f);
	
	curLean = LeanStatus::NONE;

	// graphics object

	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_TankLight = new GraphicsObject_TextureLight(ModelManager::Get("tankBodyModel"), ShaderManager::Get("textureLight"), TextureManager::Get("tankBodyTex"), LightColor, LightPos);

	// place object

	Matrix world;
	Scale.set(SCALE, 5.0f, 5.0f, 5.0f);
	RotTrans = Matrix(ROT_X, 0) * Matrix(TRANS, Xpos, 40, Zpos);
	world = Scale * RotTrans;
	pGObj_TankLight->SetWorld(world);

	// assemble tank parts 
	myTurret = new TankTurret(this, pBulletFactory);

	myRightLeg = new TankLeg(this, TankLeg::Side::RIGHT);
	myLeftLeg = new TankLeg(this, TankLeg::Side::LEFT);

	// set up collision

	Collidable::SetColliderModel(pGObj_TankLight->getModel(), VOLUME_TYPE::BSPHERE);
	Collidable::UpdateCollisionData(world);
	SetCollidableGroup<Tank>();


	GameObject::SubmitEntry();
}

Tank::~Tank()
{
	delete pGObj_TankLight;
	delete myTurret;
	delete myRightLeg;
	delete myLeftLeg;
}

void Tank::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitCollisionRegistration();
}

void Tank::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();

	//handle turret 
	myTurret->SubmitExit();
	myRightLeg->SubmitExit();
	myLeftLeg->SubmitExit();
}

void Tank::Update()
{

	Matrix world = Scale * RotTrans;
	pGObj_TankLight->SetWorld(world);
	Collidable::UpdateCollisionData(world);

	if (curLean != LeanStatus::NONE) // reset lean
	{
		if (curLean == LeanStatus::FORWARDS)
		{
			RotTrans = Matrix(ROT_X, -TankLean) * RotTrans;
		}
		else
		{
			RotTrans = Matrix(ROT_X, TankLean) * RotTrans;
		}

		curLean = LeanStatus::NONE;
	}

}

void Tank::Draw()
{
	// for testing
	//Visualizer::ShowBSphere(Collidable::GetBSphere());
	pGObj_TankLight->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}


void Tank::Forwards()
{

	RotTrans = Matrix(TRANS, Vect(0, 0, moveSpeed)) * RotTrans;

	if (curLean != LeanStatus::FORWARDS) // rotate once if not already leaning (stinky if, but cant think of another way to do it)
	{
		RotTrans = Matrix(ROT_X, TankLean) * RotTrans;
		curLean = LeanStatus::FORWARDS;
	}

	myRightLeg->MoveForwards();
	myLeftLeg->MoveForwards();
}

void Tank::Backwards()
{
	RotTrans = Matrix(TRANS, Vect(0, 0, -moveSpeed)) * RotTrans;

	if (curLean != LeanStatus::BACKWARDS)
	{
		RotTrans = Matrix(ROT_X, -TankLean) * RotTrans;
		curLean = LeanStatus::BACKWARDS;
	}

	myRightLeg->MoveBackwards();
	myLeftLeg->MoveBackwards();

}

void Tank::Left()
{
	RotTrans = Matrix(ROT_Y, rotSpeed) * RotTrans;
	XYZRot += Vect(0.0f, rotSpeed, 0.0f);

	myLeftLeg->OtherLegTurning();
	myLeftLeg->MoveBackwards();
	myRightLeg->MoveForwards();

}

void Tank::Right()
{
	RotTrans = Matrix(ROT_Y, -rotSpeed) * RotTrans;
	XYZRot += Vect(0.0f, -rotSpeed, 0.0f);

	myRightLeg->OtherLegTurning();
	myRightLeg->MoveBackwards();
	myLeftLeg->MoveForwards();

}

void Tank::Shoot()
{
	myTurret->Shoot();
}

Matrix Tank::GetRTMatrix()
{
	return RotTrans;
}

Vect Tank::GetRotation()
{
	return XYZRot;
}

void Tank::RotateTurret(Matrix rot)
{
	myTurret->Rot(rot);
}

TankTurret* Tank::GetTurret()
{
	return myTurret;
}

void Tank::SetController(TankControllerBaseClass* pC)
{
	myController = pC;
}

void Tank::Collision(Bullet*)
{
	DebugMsg::out("Collision Bullet\n");
	myController->ReportHit();

}
//
//void Tank::Collision(Tank*)
//{
//	DebugMsg::out("Collision Tank\n");
//}
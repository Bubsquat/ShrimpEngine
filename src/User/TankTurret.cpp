// turret for tank

#include "TankTurret.h"
#include "../ModelManager.h"
#include "../ShaderManager.h"
#include "../TextureManager.h"
#include "../Scene.h"
#include "../CameraManager.h"
#include "../SceneManager.h"
#include "Tank.h"
#include "BulletFactory.h"

TankTurret::TankTurret(Tank* _tank, BulletFactory* _pBulletFactory)
{
	pMyTank = _tank;
	bulletFactory = _pBulletFactory;

	TurretOffset = Vect(-10.0f, 20.0f, -10.0f);

	// graphics object

	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_TurretLight = new GraphicsObject_TextureLight(ModelManager::Get("tankTurretModel"), ShaderManager::Get("textureLight"), TextureManager::Get("tankBodyTex"), LightColor, LightPos);

	// place object

	//rotate the turret to be more horizontal 

	Matrix world;
	Scale.set(SCALE, 15.0f, 15.0f, 15.0f);
	RotTrans = Matrix(TRANS, TurretOffset) * pMyTank->GetRTMatrix();

	world = Scale * RotTrans;
	pGObj_TurretLight->SetWorld(world);

	CurrentRot = Matrix(IDENTITY);

	GameObject::SubmitEntry();

}

TankTurret::~TankTurret()
{
	delete pGObj_TurretLight;
}

void TankTurret::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	canShoot = true;
}

void TankTurret::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
}

void TankTurret::Update()
{

	Vect pos = TurretOffset * pMyTank->GetRTMatrix();

	RotTrans = Matrix(TRANS, pos);

	RotTrans = TurretDeflection * CurrentRot * RotTrans;

	Matrix world = Scale * RotTrans; // double check the order for this one
	pGObj_TurretLight->SetWorld(world);
}

void TankTurret::Draw()
{
	pGObj_TurretLight->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}

void TankTurret::Alarm0()
{
	canShoot = true;
}

void TankTurret::Shoot()
{

	if (canShoot)
	{
		bulletFactory->CreateBullet(Matrix(TRANS, BulletOffset) * RotTrans); // change this to turret offset later
		GameObject::SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 1.0f);
		canShoot = false;
	}
}

void TankTurret::Rot(Matrix _rot)
{
	CurrentRot = _rot;
}

Matrix TankTurret::GetRTMatrix()
{
	return RotTrans;
}